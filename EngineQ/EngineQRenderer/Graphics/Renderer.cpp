#include "Renderer.hpp"

#include <Libraries/GL/glew.h>

#include "Mesh.hpp"
#include "Framebuffer.hpp"
#include "ShaderProperties.hpp"
#include "Scene.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		void Renderer::SetDeferred(bool state)
		{
			if (state)
				shaderMethod = &Graphics::Renderable::GetDeferredShader;
			else
				shaderMethod = &Graphics::Renderable::GetForwardShader;
			deferred = state;
		}

		void Renderer::Render(Scene& scene) const
		{
			if (this->framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				this->framebuffer->Bind();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			auto camera = scene.GetActiveCamera();
			int i = 0;
			for(auto renderable : scene.GetRenderables())
			{
				i++;
				auto mesh = renderable->GetMesh();
				Graphics::Mesh& p = *mesh;

				ShaderProperties* shader;
				if (deferred)
					shader = renderable->GetDeferredShader();
				else
					shader = renderable->GetForwardShader();

				const auto& matrices = shader->GetMatrices();

				matrices.Model = renderable->GetGlobalMatrix();
				matrices.View = camera->GetViewMatrix();
				matrices.Projection = camera->GetProjectionMatrix();

				// TMP
				auto cameraPosition = shader->TryGetProperty<Math::Vector3>("cameraPosition");
				if (cameraPosition != nullval)
					*cameraPosition = camera->GetPosition();

				auto time = shader->TryGetProperty<float>("time");
				if (time != nullval)
					*time = 0;

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
