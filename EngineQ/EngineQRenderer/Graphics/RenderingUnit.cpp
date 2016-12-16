#include <map>
#include <Utilities/ResourcesIDs.hpp>

#include "RenderingUnit.hpp"
#include "PostprocessingExceptions.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Shadows/Light.hpp"


namespace EngineQ
{
	namespace Graphics
	{

		void InitScreenQuad(GLuint* quadVao)
		{
			GLfloat quadVertices[] = {
				-1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,

				1.0f, -1.0f,  1.0f, 0.0f,
				-1.0f,  1.0f,  0.0f, 1.0f,
				1.0f,  1.0f,  1.0f, 1.0f
			};

			GLuint  quadVBO;
			glGenVertexArrays(1, quadVao);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(*quadVao);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
			glBindVertexArray(0);
		}

		void RenderingUnit::CreateTexture(GLuint* texture, const Configuration::TextureConfiguration& configuration) const
		{
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			auto size = screenDataProvider->GetScreenSize();
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.InternalFormat, size.X, size.Y, 0, configuration.Format, configuration.DataType, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		Resources::Resource<Texture> RenderingUnit::CreateTexture(int width, int height, const Configuration::TextureConfiguration& configuration)
		{
			return Resources::Resource<Texture>(std::make_unique<Texture>(width, height, configuration));
		}

		void RenderingUnit::Resize(int width, int height)
		{
			glViewport(0, 0, width, height);

			//for (std::size_t i = 0; i < textures.size(); i++)
			//{
			//	glBindTexture(GL_TEXTURE_2D, textures[i]);
			//	glTexImage2D(GL_TEXTURE_2D, 0, texturesConfigurations[i].InternalFormat, width, height, 0, texturesConfigurations[i].Format, texturesConfigurations[i].DataType, nullptr);
			//}
			for (auto& tex : texturesResources)
				tex->Resize(width, height);
		}


		std::unique_ptr<Framebuffer> RenderingUnit::CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting)
		{
			return std::make_unique<Framebuffer>(depthTesting, textures, screenDataProvider);
		}

		std::unique_ptr<Framebuffer> RenderingUnit::CreateFramebuffer(std::vector<Resources::Resource<Texture>>& textures, bool depthTesting)
		{
			return std::make_unique<Framebuffer>(depthTesting, textures, screenDataProvider);
		}

		void RenderingUnit::Init(const Configuration::RenderingUnitConfiguration& configuration)
		{
			auto size = screenDataProvider->GetScreenSize();
			//textures
			std::map<std::string, int> texturesNames;
			int j = 0;
			for (auto texConfiguration : configuration.Textures)
			{
				//CreateTexture(&textures[j], texConfiguration);
				//texturesConfigurations.push_back(texConfiguration);
				texturesResources.push_back(CreateTexture(size.X, size.Y, texConfiguration));
				texturesNames.emplace(std::string(texConfiguration.Name), j);
				++j;
			}

			//renderer

			renderer.SetDeferred(!configuration.Renderer.Deffered);
			renderer.SetGlobalShadows(configuration.Renderer.GlobalShadows);

			if (configuration.Renderer.Output.size() == 0 || (configuration.Renderer.Output.size() == 1 && configuration.Renderer.Output[0].Texture == "Screen"))
				renderer.SetTargetBuffer(nullptr);
			else
			{
				std::vector<Resources::Resource<Texture>> rendererOutput;
				rendererOutput.reserve(configuration.Renderer.Output.size());
				for (auto outputConfiguration : configuration.Renderer.Output)
					rendererOutput.push_back(texturesResources[texturesNames[outputConfiguration.Texture]]);
				renderer.SetTargetBuffer(CreateFramebuffer(rendererOutput, true));
			}

			//effects
			for (auto effect : configuration.Effects)
			{
				auto shaderPass = std::make_unique<ShaderPass>(effect.Shader);
				for (auto inputConfiguration : effect.Input)
					shaderPass->AddInput(InputConfiguration{ texturesResources[texturesNames[inputConfiguration.Texture]],inputConfiguration.LocationName });

				if (effect.Output.size() == 0 || (effect.Output.size() == 1 && effect.Output[0].Texture == "Screen"))
					shaderPass->SetTargetBuffer(nullptr);
				else
				{
					std::vector<Resources::Resource<Texture>> output;
					output.reserve(effect.Output.size());
					for (auto k : effect.Output)
						output.push_back(texturesResources[texturesNames[k.Texture]]);//check if output is set  to "screen", or check this for last effect?
					auto fb = CreateFramebuffer(output, effect.DepthTesting);
					shaderPass->SetTargetBuffer(std::move(fb));

				}
				shaderPass->SetApplyShadowData(effect.ApplyShadowInfo);
				effects.push_back(std::move(shaderPass));
			}
		}

		RenderingUnit::RenderingUnit(ScreenDataProvider* dataProvider, const Configuration::RenderingUnitConfiguration& configuration) :
			screenDataProvider(dataProvider), handler(*this, &RenderingUnit::Resize)
		{
			//	glPolygonMode(GL_FRONT, GL_FILL);
			//	glPolygonMode(GL_BACK, GL_LINE);
			//	glPolygonMode(GL_FRONT, GL_LINE);
			//	glPolygonMode(GL_BACK, GL_LINE);

			glFrontFace(GL_CW);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);

			glEnable(GL_DEPTH_TEST);
			//	glClearDepth(0);
			//	glDepthFunc(GL_GREATER);

			screenDataProvider->resizeEvent += handler;

			InitScreenQuad(&quadVao);

			Init(configuration);
		}

		RenderingUnit::~RenderingUnit()
		{
			screenDataProvider->resizeEvent -= handler;
		}

		void RenderingUnit::Render(Scene& scene)
		{
			renderer.Render(scene, screenDataProvider);

			auto& sceneLights = scene.GetLights();
			if (effects.size() > 0)
			{
				glDisable(GL_DEPTH_TEST);

				for (auto& effect : effects)
				{
					effect->BindTargetBuffer();

					glClear(GL_COLOR_BUFFER_BIT);
					glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
					auto& shader = effect->GetShaderproperties();

					auto& lights = shader.GetLights();
					int lightsCount = sceneLights.size() > lights.size() ? lights.size() : sceneLights.size();
					for (int i = 0; i < lightsCount; i++)
					{
						lights[i].Diffuse = Math::Vector3f(0.5f);
						lights[i].Ambient = Math::Vector3f(0.5f);
						lights[i].Specular = Math::Vector3f(0.5f);
						lights[i].Position = sceneLights[i]->GetPosition();
						lights[i].CastsShadows = sceneLights[i]->GetCastShadows();
					}

					if (effect->GetApplyShadowData())
					{
						for (int i = 0; i < lightsCount; i++)
						{
							if (lights[i].ShadowMap.IsSet())
								lights[i].ShadowMap.Set(sceneLights[i]->GetDepthTexture());
						}
					}

					effect->Activate(scene.GetActiveCamera(), 0);
					glBindVertexArray(quadVao);

					effect->BindTextures();
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
				}

				glEnable(GL_DEPTH_TEST);
			}
			Framebuffer::BindDefault();

		}
	}
}
