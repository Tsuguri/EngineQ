#include "RenderingUnit.hpp"

// Standard includes
#include <map>

// This project
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

		Resources::Resource<Texture> RenderingUnit::CreateTexture(int width, int height, const Configuration::TextureConfiguration& configuration)
		{
			return Resources::Resource<Texture>(std::make_unique<Texture>(width, height, configuration));
		}

		void RenderingUnit::Resize(int width, int height)
		{
			glViewport(0, 0, width, height);

			for (auto& tex : texturesResources)
				tex->Resize(width, height);
		}


		std::unique_ptr<Framebuffer> RenderingUnit::CreateFramebuffer(std::vector<Resources::Resource<Texture>>& textures, bool depthTesting)
		{
			return std::make_unique<Framebuffer>(depthTesting, textures, screenDataProvider);
		}

		void RenderingUnit::Initialize(const Configuration::RenderingUnitConfiguration& configuration)
		{
			auto size = screenDataProvider->GetScreenSize();

			// Textures
			int j = 0;
			std::map<std::string, int> textureNames;

			for (auto texConfiguration : configuration.Textures)
			{
				texturesResources.push_back(CreateTexture(size.X, size.Y, texConfiguration));
				textureNames.emplace(std::string(texConfiguration.Name), j);
				++j;
			}

			// Renderer
			renderer.SetDeferred(!configuration.Renderer.Deffered);
			renderer.SetGlobalShadows(configuration.Renderer.GlobalShadows);

			if (configuration.Renderer.Output.size() == 0 || (configuration.Renderer.Output.size() == 1 && configuration.Renderer.Output[0].Texture == "Screen"))
			{
				renderer.SetTargetBuffer(nullptr);
			}
			else
			{
				std::vector<Resources::Resource<Texture>> rendererOutput;
				rendererOutput.reserve(configuration.Renderer.Output.size());
				for (auto outputConfiguration : configuration.Renderer.Output)
					rendererOutput.push_back(texturesResources[textureNames.at(outputConfiguration.Texture)]);
				renderer.SetTargetBuffer(CreateFramebuffer(rendererOutput, true));
			}

			// Effects
			this->AddEffects(configuration.Effects, textureNames);
		}

		void RenderingUnit::AddEffects(const std::vector<Configuration::EffectConfiguration>& effects, const std::map<std::string, int>& textureNames)
		{
			for (const auto& effect : effects)
			{
				if (effect.Iterations < 0)
				{
					auto shaderPass = this->shaderPassFactory->CreateShaderPass(effect);
					for (auto inputConfiguration : effect.Input)
						shaderPass->AddInput(InputConfiguration{ texturesResources[textureNames.at(inputConfiguration.Texture)], inputConfiguration.LocationName });

					if (effect.Output.size() == 0 || (effect.Output.size() == 1 && effect.Output[0].Texture == "Screen"))
					{
						shaderPass->SetTargetBuffer(nullptr);
					}
					else
					{
						std::vector<Resources::Resource<Texture>> output;
						output.reserve(effect.Output.size());
						for (auto outputTexture : effect.Output)
							output.push_back(texturesResources[textureNames.at(outputTexture.Texture)]);//check if output is set  to "screen", or check this for last effect?
					
						shaderPass->SetTargetBuffer(CreateFramebuffer(output, effect.DepthTesting));
					}

					shaderPass->SetApplyShadowData(effect.ApplyShadowInfo);
					auto shaderPassPtr = shaderPass.get();

					this->effects.push_back(std::move(shaderPass));

					shaderPassPtr->Created();
				}
				else
				{
					for (int i = 0; i < effect.Iterations; ++i)
					{
						this->AddEffects(effect.Effects, textureNames);
					}
				}
			}
		}

		RenderingUnit::RenderingUnit(ScreenDataProvider* dataProvider, const Configuration::RenderingUnitConfiguration& configuration, std::unique_ptr<ShaderPassFactory> shaderPassFactory) :
			shaderPassFactory(std::move(shaderPassFactory)), screenDataProvider(dataProvider), handler(*this, &RenderingUnit::Resize)
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
		}

		RenderingUnit::RenderingUnit(ScreenDataProvider* dataProvider, const Configuration::RenderingUnitConfiguration& configuration) :
			RenderingUnit(dataProvider, configuration, std::make_unique<ShaderPassFactory>())
		{
			Initialize(configuration);
		}

		RenderingUnit::~RenderingUnit()
		{
			screenDataProvider->resizeEvent -= handler;
		}

		void RenderingUnit::Render(Scene& scene)
		{
			renderer.Render(scene, screenDataProvider);

			auto& camera = *scene.GetActiveCamera();

			auto& sceneLights = scene.GetLights();
			if (effects.size() > 0)
			{
				glDisable(GL_DEPTH_TEST);

				for (auto& effect : effects)
				{
					effect->BeforeRender();

					effect->BindTargetBuffer();

					glClear(GL_COLOR_BUFFER_BIT);
					glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
					auto& shader = effect->GetShaderProperties();

					shader.GetMatrices().View = camera.GetViewMatrix();
					shader.GetMatrices().Projection = camera.GetProjectionMatrix();



					if (effect->GetApplyShadowData())
					{
						auto& lights = shader.GetLights();
						auto lightsCount = sceneLights.size() > lights.size() ? lights.size() : sceneLights.size();
						shader.GetLightCount() = static_cast<GLint>(lightsCount);

						for (std::size_t i = 0; i < lightsCount; ++i)
						{
							auto& light = lights[i];
							auto sceneLight = sceneLights[i];
							sceneLight->SetLightInShader(light);
						}
					}

					effect->Activate(scene.GetActiveCamera(), 0);
					glBindVertexArray(quadVao);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);

					effect->AfterRender();
				}

				glEnable(GL_DEPTH_TEST);
			}
			Framebuffer::BindDefault();

		}
	}
}
