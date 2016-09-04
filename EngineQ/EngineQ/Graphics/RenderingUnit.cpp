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

		RenderingUnit::RenderingUnit(Engine* engine) : renderer(new ForwardRenderer{}), effect(engine->GetResourceManager()->GetResource<Shader>(Utilities::ResourcesIDs::QuadShader))
		{
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glClearDepth(0);
			glDepthFunc(GL_GREATER);



			if (!frm.Ready())
				std::cout << "framebuffer is still not complete!" << std::endl;
			Framebuffer::BindDefault();
			InitScreenQuad(&quadVao);
		}

		RenderingUnit::~RenderingUnit()
		{
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
			Framebuffer::BindDefault();

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glDisable(GL_DEPTH_TEST);

			effect.Activate();
			glBindVertexArray(quadVao);
			glBindTexture(GL_TEXTURE_2D, frm.GetColorTexture(0));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);




		}
	}
}
