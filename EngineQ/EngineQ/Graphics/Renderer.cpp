#include <GL/glew.h>

#include "../TimeCounter.hpp"
#include "Renderer.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		void Renderer::SetDeferred(bool state)
		{
			if (state)
				shaderMethod = &Renderable::GetDeferredShader;
			else
				shaderMethod = &Renderable::GetForwardShader;
			deferred = state;
		}

		void Renderer::Render(Scene* scene) const
		{
			if (framebuffer == nullptr)
			{
				Framebuffer::BindDefault();
			}
			else
				framebuffer->Bind();


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			Mesh* mesh;
			Shader* shd;
			auto cam = scene->ActiveCamera();

			Utilities::Nullable<UniformLocation> tmp;

			for (auto it = scene->RenderablesBegin(), end = scene->RenderablesEnd(); it != end; ++it)
			{
				mesh = (*it)->GetModel();


				shd = ((*it)->*shaderMethod)();

				shd->Activate();

				tmp = shd->TryGetUniformLocation("ViewMat");
				if (tmp != nullval)
					shd->Bind(*tmp, cam->GetViewMatrix());
				tmp = shd->TryGetUniformLocation("ProjMat");
				if (tmp != nullval)
					shd->Bind(*tmp, cam->GetProjectionMatrix());
				tmp = shd->TryGetUniformLocation("ModelMat");
				if (tmp != nullval)
					shd->Bind(*tmp, (*it)->GetEntity().GetTransform().GetGlobalMatrix());
				tmp = shd->TryGetUniformLocation("cameraPosition");
				if (tmp != nullval)
					shd->Bind(*tmp, cam->GetEntity().GetTransform().GetPosition());

				tmp = shd->TryGetUniformLocation("time");
				if (tmp != nullval)
					shd->Bind(*tmp, TimeCounter::Get()->TimeFromStart());

				tmp = shd->TryGetUniformLocation("ambientStrength");
				if (tmp != nullval)
					shd->Bind(*tmp, 0.4f);
				tmp = shd->TryGetUniformLocation("specularStrength");
				if (tmp != nullval)
					shd->Bind(*tmp, 0.05f);
				tmp = shd->TryGetUniformLocation("materialShininess");
				if (tmp != nullval)
					shd->Bind(*tmp, 16);




				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, nullptr);
			}
		}

		void Renderer::SetTargetBuffer(std::shared_ptr<Framebuffer> buffer)
		{
			framebuffer = buffer;
		}
	}
}
