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

		void RenderingUnit::Init(RendererConfiguration* configuration)
		{
			//textures
			std::map<std::string, int> texName;
			int j = 0;
			for (auto i : configuration->Textures)
			{
				CreateTexture(&textures[j], i);
				texturesConfigurations.push_back(i);
				texName.emplace(std::string(i.name), j);
				++j;
			}
			auto rm = engine->GetResourceManager();
			//effects
			for (auto i : configuration->Effects)
			{
				auto p = new PostprocessingEffect{ rm->GetResource<Shader>(i.Shader) };
				for (auto k : i.Input)
				{
					p->AddInput(InputConfiguration{ PostprocessingEffect::textureLocations[k.Location],textures[texName[k.Texture]] });
				}

				std::vector<GLuint> output(i.Output.size());
				for (auto k : i.Output)
					output.push_back(textures[texName[k.Texture]]);//check if output is set  to "screen", or check this for last effect?
				auto fb = new Framebuffer(i.DepthTesting, output);
				p->SetTargetBuffer(fb);
				framebuffers.push_back(std::shared_ptr<Framebuffer>{fb});
				effects.push_back(std::shared_ptr<PostprocessingEffect>{p});
				//tutaj ogarn¹æ wynik ostatniego efektu
			}
		}

		RenderingUnit::RenderingUnit(Engine* engine, RendererConfiguration* configuration) : engine(engine), renderer(new ForwardRenderer{}), effect(engine->GetResourceManager()->GetResource<Shader>(Utilities::ResourcesIDs::QuadShader)), textures(configuration->Textures.size(), 0), texturesConfigurations(configuration->Textures.size()), handler(*this, &RenderingUnit::Resize)
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

			if (!frm.Ready())
				std::cout << "framebuffer is still not complete!" << std::endl;
			Framebuffer::BindDefault();
			InitScreenQuad(&quadVao);

			Init(configuration);
		}

		RenderingUnit::~RenderingUnit()
		{
			engine->resizeEvent -= handler;

			glDeleteTextures(textures.size(), &textures[0]);

			if (renderer != nullptr)
				delete renderer;
		}

		void RenderingUnit::Render(Scene* scene)
		{

			frm.Bind();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderer->Render(scene);
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
