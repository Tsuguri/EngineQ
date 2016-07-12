#include "ForwardRenderer.hpp"
#include <GL/glew.h>

namespace EngineQ
{
	namespace Graphics
	{
		ForwardRenderer::ForwardRenderer()
		{
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}

		ForwardRenderer::~ForwardRenderer()
		{

		}

		void ForwardRenderer::Render(Scene* scene)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Mesh* mesh;
			Shader* shd;
			auto cam = scene->ActiveCamera();


			for (auto it = scene->RenderablesBegin(), end = scene->RenderablesEnd(); it != end; ++it)
			{
				mesh = (*it)->Model();
				shd = (*it)->ForwardShader();

				shd->Activate();
				shd->Bind(shd->GetUniformLocation("ViewMat"), cam->ViewMatrix());

				shd->Bind(shd->GetUniformLocation("ProjMat"), cam->ProjectionMatrix());

				shd->Bind(shd->GetUniformLocation("ModelMat"),(*it)->GetEntity().GetTransform().GetGlobalMatrix() );

				glBindVertexArray(mesh->vao);
				glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, NULL);
			}
			
		}
	}
}
