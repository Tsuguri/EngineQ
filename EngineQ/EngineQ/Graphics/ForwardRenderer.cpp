#include <GL/glew.h>

#include "../TimeCounter.hpp"
#include "ForwardRenderer.hpp"

namespace EngineQ
{
	namespace Graphics
	{


		ForwardRenderer::ForwardRenderer()
		{


		}

		ForwardRenderer::~ForwardRenderer()
		{
		}

		void ForwardRenderer::Render(Scene* scene)
		{
			/*if (framebuffer == nullptr)
			{
				Framebuffer::BindDefault();
			}
			else
				framebuffer->Bind();

			if (!framebuffer->Ready())
				throw 1;*/


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
		}

		void ForwardRenderer::SetTargetBuffer(std::shared_ptr<Framebuffer> buffer)
		{
			framebuffer = buffer;
		}
	}
}
