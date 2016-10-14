#include "RenderingUnit.hpp"
#include "PostprocessingExceptions.hpp"
#include "../Utilities/ResourcesIDs.hpp"
#include "../Engine.hpp"
#include "Renderer.hpp"
#include "../TimeCounter.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		void InitScreenQuad(GLuint* quadVao)
		{
			GLfloat quadVertices[] = {
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
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

		void RenderingUnit::CreateTexture(GLuint* texture, const TextureConfiguration& configuration) const
		{
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			auto size = engine->GetScreenSize();
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.InternalFormat, size.X, size.Y, 0, configuration.Format, configuration.DataType, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void RenderingUnit::Resize(int width, int height)
		{
			for (int i = 0; i < textures.size(); i++)
			{
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, texturesConfigurations[i].InternalFormat, width, height, 0, texturesConfigurations[i].Format, texturesConfigurations[i].DataType, nullptr);
			}
		}


		std::unique_ptr<Framebuffer> RenderingUnit::CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting)
		{
			return std::make_unique<Framebuffer>(depthTesting, textures, engine);

		}

		void RenderingUnit::Init(const RenderingUnitConfiguration& configuration)
		{
			//textures
			std::map<std::string, int> texturesNames;
			int j = 0;
			for (auto texConfiguration : configuration.Textures)
			{
				CreateTexture(&textures[j], texConfiguration);
				texturesConfigurations.push_back(texConfiguration);
				texturesNames.emplace(std::string(texConfiguration.Name), j);
				++j;
			}

			//renderer

			renderer.SetDeferred(!configuration.Renderer.Deffered);

			if (configuration.Renderer.Output.size() == 0 || (configuration.Renderer.Output.size() == 1 && configuration.Renderer.Output[0].Texture == "Screen"))
				renderer.SetTargetBuffer(nullptr);
			else
			{
				std::vector<GLuint> rendererOutput;
				rendererOutput.reserve(configuration.Renderer.Output.size());
				for (auto outputConfiguration : configuration.Renderer.Output)
					rendererOutput.push_back(textures[texturesNames[outputConfiguration.Texture]]);
				renderer.SetTargetBuffer(CreateFramebuffer(rendererOutput, true));
			}

			auto rm = engine->GetResourceManager();

			//effects
			for (auto shaderPass : configuration.Effects)
			{
				auto p = std::make_unique<ShaderPass>(rm->GetResource<Shader>(shaderPass.Shader));
				for (auto inputConfiguration : shaderPass.Input)
					p->AddInput(InputConfiguration{ inputConfiguration.Location,textures[texturesNames[inputConfiguration.Texture]],inputConfiguration.LocationName });

				if (shaderPass.Output.size() == 0 || (shaderPass.Output.size() == 1 && shaderPass.Output[0].Texture == "Screen"))
					p->SetTargetBuffer(nullptr);
				else
				{
					std::vector<GLuint> output;
					output.reserve(shaderPass.Output.size());
					for (auto k : shaderPass.Output)
						output.push_back(textures[texturesNames[k.Texture]]);//check if output is set  to "screen", or check this for last effect?
					auto fb = CreateFramebuffer(output, shaderPass.DepthTesting);
					p->SetTargetBuffer(std::move(fb));

				}
				effects.push_back(std::move(p));
			}
		}

		RenderingUnit::RenderingUnit(Engine* engine, const RenderingUnitConfiguration& configuration) : engine(engine), textures(configuration.Textures.size(), 0), handler(*this, &RenderingUnit::Resize)
		{
		//	glEnable(GL_DEPTH_TEST);
		//	glEnable(GL_CULL_FACE);
		//	glPolygonMode(GL_FRONT, GL_FILL);
		//	glPolygonMode(GL_BACK, GL_LINE);
		//	glPolygonMode(GL_FRONT, GL_LINE);
		//	glPolygonMode(GL_BACK, GL_LINE);
			
			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);
		//	glEnable(GL_CULL_FACE);

			glEnable(GL_DEPTH_TEST);
		//	glClearDepth(0);
		//	glDepthFunc(GL_GREATER);

			engine->resizeEvent += handler;

			InitScreenQuad(&quadVao);

			Init(configuration);
		}

		RenderingUnit::~RenderingUnit()
		{
			engine->resizeEvent -= handler;

			if (textures.size() > 0)
				glDeleteTextures(textures.size(), &textures[0]);

		}

		void RenderingUnit::Render(Scene* scene)
		{

			renderer.Render(scene);



			if (effects.size() > 0)
			{
				glDisable(GL_DEPTH_TEST);

				for (auto& effect : effects)
				{
					effect->BindTargetBuffer();

					glClear(GL_COLOR_BUFFER_BIT);
					glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
					
					effect->Activate(scene->ActiveCamera(), TimeCounter::Get()->TimeFromStart());
					glBindVertexArray(quadVao);

					effect->BindTextures();
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
					effect->UnbindTextures();
				}
				
				glEnable(GL_DEPTH_TEST);
			}
			Framebuffer::BindDefault();

		}
	}
}
