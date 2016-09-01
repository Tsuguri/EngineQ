#include <GL/glew.h>

#include "../TimeCounter.hpp"
#include "ForwardRenderer.hpp"
#include "../Engine.hpp"
#include "../Utilities/ResourcesIDs.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		void ForwardRenderer::InitScreenQuad()
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
			glGenVertexArrays(1, &quadVao);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVao);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
			glBindVertexArray(0);
		}

		ForwardRenderer::ForwardRenderer(EngineQ::Engine* engine)
		{
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);
		//	glCullFace(GL_BACK);
			//glEnable(GL_CULL_FACE);
			//frm.AddColorAttachment();
			//frm.AddDepthTesting();
			glClearDepth(0);
			glDepthFunc(GL_GREATER);



			if (!frm.Ready())
				std::cout << "framebuffer is still not complete!" << std::endl;
			Framebuffer::BindDefault();

			quadShader = engine->GetResourceManager()->GetResource<Shader>(Utilities::ResourcesIDs::QuadShader);

			InitScreenQuad();

		}

		ForwardRenderer::~ForwardRenderer()
		{
		}

		void ForwardRenderer::Render(Scene* scene)
		{

			//frm.Bind();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			//glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT	);
			Mesh* mesh;
			Shader* shd;
			auto cam = scene->ActiveCamera();

			Utilities::Nullable<UniformLocation> tmp;

			for (auto it = scene->RenderablesBegin(), end = scene->RenderablesEnd(); it != end; ++it)
			{
				mesh = (*it)->GetModel();
				shd = (*it)->GetForwardShader();

				shd->Activate();
				shd->Bind(shd->GetUniformLocation("ViewMat"), cam->GetViewMatrix());
				shd->Bind(shd->GetUniformLocation("ProjMat"), cam->GetProjectionMatrix());
				shd->Bind(shd->GetUniformLocation("ModelMat"), (*it)->GetEntity().GetTransform().GetGlobalMatrix());
				shd->Bind(shd->GetUniformLocation("cameraPosition"), cam->GetEntity().GetTransform().GetPosition());

				tmp = shd->TryGetUniformLocation("time");
				if (tmp!=nullval)
					shd->Bind(*tmp, TimeCounter::Get()->TimeFromStart());

				shd->Bind(shd->GetUniformLocation("ambientStrength"), 0.4f);
				//	shd->Bind(shd->GetUniformLocation("specularStrength"), 0.05f);
				shd->Bind(shd->GetUniformLocation("materialShininess"), 16);




				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, nullptr);
			}

			//Framebuffer::BindDefault();

			//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			//glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			//glDisable(GL_DEPTH_TEST);

			//quadShader->Activate();
			//glBindVertexArray(quadVao);
			//glBindTexture(GL_TEXTURE_2D, frm.GetColorTexture(0));
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			//glBindVertexArray(0);

		}
	}
}
