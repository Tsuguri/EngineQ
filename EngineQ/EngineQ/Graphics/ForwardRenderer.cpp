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

			//uniform vec3 lightDir = vec3(-1, -1, 0);
			//uniform vec3 lightColor = vec3(1, 1, 1);


			for (auto it = scene->RenderablesBegin(), end = scene->RenderablesEnd(); it != end; ++it)
			{
				mesh = (*it)->GetModel();
				shd = (*it)->GetForwardShader();

				shd->Activate();
				shd->Bind(shd->GetUniformLocation("ViewMat"), cam->GetViewMatrix());
				shd->Bind(shd->GetUniformLocation("ProjMat"), cam->GetProjectionMatrix());
				shd->Bind(shd->GetUniformLocation("ModelMat"),(*it)->GetEntity().GetTransform().GetGlobalMatrix() );
				shd->Bind(shd->GetUniformLocation("cameraPosition"),cam->GetEntity().GetTransform().GetPosition() );

				shd->Bind(shd->GetUniformLocation("ambientStrength"), 0.4f);
			//	shd->Bind(shd->GetUniformLocation("specularStrength"), 0.05f);
				shd->Bind(shd->GetUniformLocation("materialShininess"), 16);





				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, nullptr);
			}
			
		}
	}
}
