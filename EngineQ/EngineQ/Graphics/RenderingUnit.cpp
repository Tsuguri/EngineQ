#include "RenderingUnit.hpp"
#include "PostprocessingExceptions.hpp"
#include "../Utilities/ResourcesIDs.hpp"
#include "../Engine.hpp"
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

		void RenderingUnit::CreateTexture(GLuint* texture, TextureConfiguration configuration)
		{
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			auto size = Engine::Get()->GetScreenSize();
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.Format, size.X, size.Y, 0, configuration.Format, configuration.DataType, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void RenderingUnit::Resize(int width, int height)
		{
			for (int i = 0; i < textures.size(); i++)
			{
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, texturesConfigurations[i].Format, width, height, 0, texturesConfigurations[i].Format, texturesConfigurations[i].DataType, nullptr);
			}
			for (auto it = framebuffers.begin(); it != framebuffers.end(); ++it)
			{
				(*it)->Resize(width, height);
			}
		}


		std::shared_ptr<Framebuffer> RenderingUnit::CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting)
		{
			return std::make_shared<Framebuffer>(depthTesting, textures, engine);

		}

		void RenderingUnit::Init(RenderingUnitConfiguration* configuration)
		{
			//textures
			std::map<std::string, int> texName;
			int j = 0;
			for (auto i : configuration->Textures)
			{
				CreateTexture(&textures[j], i);
				texturesConfigurations.push_back(i);
				texName.emplace(std::string(i.Name), j);
				++j;
			}

			if (configuration->Renderer.Deffered)
			{
				//should never happen as for now
			}
			else
			{
				renderer = new ForwardRenderer{};
				if (configuration->Renderer.Output.size() == 0 || (configuration->Renderer.Output.size() == 1 && configuration->Renderer.Output[0].Texture == "Screen"))
					renderer->SetTargetBuffer(nullptr);
				else
				{
					std::vector<GLuint> output;
					output.reserve(configuration->Renderer.Output.size());
					for (auto k : configuration->Renderer.Output)
						output.push_back(textures[texName[k.Texture]]);
					renderer->SetTargetBuffer(CreateFramebuffer(output, true));
				}
			}



			auto rm = engine->GetResourceManager();
			//effects
			for (auto i : configuration->Effects)
			{
				auto p = new PostprocessingEffect{ rm->GetResource<Shader>(i.Shader) };
				for (auto k : i.Input)
				{
					auto g = texName[k.Texture];
					auto z = textures[g];
					p->AddInput(InputConfiguration{ PostprocessingEffect::textureLocations[k.Location],z });
				}
				if (i.Output.size() == 0 || (i.Output.size() == 1 && i.Output[0].Texture == "Screen"))
					p->SetTargetBuffer(nullptr);
				else
				{

					std::vector<GLuint> output;
					output.reserve(i.Output.size());
					for (auto k : i.Output)
						output.push_back(textures[texName[k.Texture]]);//check if output is set  to "screen", or check this for last effect?
					auto fb = CreateFramebuffer(output, i.DepthTesting);

					p->SetTargetBuffer(fb);

				}
				effects.push_back(std::shared_ptr<PostprocessingEffect>(p));
				//tutaj ogarn¹æ wynik ostatniego efektu
			}
		}

		RenderingUnit::RenderingUnit(Engine* engine, RenderingUnitConfiguration* configuration) : engine(engine), textures(configuration->Textures.size(), 0), texturesConfigurations(configuration->Textures.size()), handler(*this, &RenderingUnit::Resize)
		{
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glClearDepth(0);
			glDepthFunc(GL_GREATER);

			engine->resizeEvent += handler;

			Framebuffer::BindDefault();
			InitScreenQuad(&quadVao);

			Init(configuration);
		}

		RenderingUnit::~RenderingUnit()
		{
			engine->resizeEvent -= handler;

			if (textures.size() > 0)
				glDeleteTextures(textures.size(), &textures[0]);

			if (renderer != nullptr)
				delete renderer;
		}

		void RenderingUnit::Render(Scene* scene)
		{



			renderer->Render(scene);

			//if (effects.size() > 0)
			//	for (auto& i : effects)
			//	{
			//		i->BindTargetBuffer();

			//		glClear(GL_COLOR_BUFFER_BIT);
			//		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			//		glDisable(GL_DEPTH_TEST);
			//		i->Activate();
			//		glBindVertexArray(quadVao);
			//		i->BindTextures();
			//		glDrawArrays(GL_TRIANGLES, 0, 6);
			//		glBindVertexArray(0);
			//		//i->UnbindTextures();
			//	}


			//OLD
			/*Framebuffer::BindDefault();

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glDisable(GL_DEPTH_TEST);

			effect.Activate();
			glBindVertexArray(quadVao);
			glBindTexture(GL_TEXTURE_2D, frm.GetColorTexture(0));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);*/




		}
	}
}
