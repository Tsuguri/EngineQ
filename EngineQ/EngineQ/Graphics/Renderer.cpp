#include "Renderer.hpp"

#include <GL/glew.h>

#include "Mesh.hpp"
#include "Framebuffer.hpp"
#include "ShaderProperties.hpp"
#include "../TimeCounter.hpp"
#include "../Objects/Renderable.hpp"
#include "../Objects/Camera.hpp"
#include "../Objects/Entity.hpp"
#include "../Objects/Transform.hpp"
#include "../Objects/Renderable.hpp"

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
			if (this->framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				this->framebuffer->Bind();


			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			auto camera = scene->ActiveCamera();

			for (auto it = scene->RenderablesBegin(), end = scene->RenderablesEnd(); it != end; ++it)
			{
				auto mesh = (*it)->GetMesh();
				auto shader = ((*it)->*shaderMethod)();

				const auto& matrices = shader->GetMatrices();

				matrices.Model = (*it)->GetEntity().GetTransform().GetGlobalMatrix();
				matrices.View = camera->GetViewMatrix();
				matrices.Projection = camera->GetProjectionMatrix();

				// TMP
				auto cameraPosition = shader->TryGetProperty<Math::Vector3>("cameraPosition");
				if (cameraPosition != nullval)
					*cameraPosition = camera->GetEntity().GetTransform().GetPosition();

				auto time = shader->TryGetProperty<float>("time");
				if (time != nullval)
					*time = TimeCounter::Get()->TimeFromStart();

				auto ambientStrength = shader->TryGetProperty<float>("ambientStrength");
				if (ambientStrength != nullval)
					*ambientStrength = 0.4f;

				auto specularStrength = shader->TryGetProperty<float>("specularStrength");
				if (specularStrength != nullval)
					*specularStrength = 0.05f;
				
				auto materialShininess = shader->TryGetProperty<float>("materialShininess");
				if (materialShininess != nullval)
					*materialShininess = 16;

				shader->Apply();


				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
			}
		}

		void Renderer::SetTargetBuffer(std::shared_ptr<Framebuffer> buffer)
		{
			framebuffer = buffer;
		}
	}
}
