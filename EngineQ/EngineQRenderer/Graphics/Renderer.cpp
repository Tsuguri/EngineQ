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
			// Sets method pointer for getting shader from renderables for rendering (if optimization)
			// Currently not used
			// TODO: MAKE THIS WORK
			if (state)
				shaderMethod = &Graphics::Renderable::GetDeferredShader;
			else
				shaderMethod = &Graphics::Renderable::GetForwardShader;
			deferred = state;
		}

		void Renderer::Render(Scene& scene) const
		{
			// Render target binding

			if (this->framebuffer == nullptr)
				// Binds default buffer - screen
				Framebuffer::BindDefault();
			else
				this->framebuffer->Bind();

			// Render target color buffer and depth buffer clearing:

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Rendering from scene active camera pointview 
			auto camera = scene.GetActiveCamera();

			// Renders each object from vector get from scene

			for(auto renderable : scene.GetRenderables())
			{
				auto mesh = renderable->GetMesh();
				Graphics::Mesh& p = *mesh;

				ShaderProperties* shader;
				// Gets shader propertis of proper shader
				// Unfortunatelly doesn't work through pointer - to investigation
				// TODO: MAKE THIS WORK THROUGH METHOD POINTER
				if (deferred)
					shader = renderable->GetDeferredShader();
				else
					shader = renderable->GetForwardShader();

				// Standard shader MVP matrices filled from rendered object and camera
				const auto& matrices = shader->GetMatrices();

				matrices.Model = renderable->GetGlobalMatrix();
				matrices.View = camera->GetViewMatrix();
				matrices.Projection = camera->GetProjectionMatrix();

				// TMP - TODO - remove this hack
				auto cameraPosition = shader->TryGetProperty<Math::Vector3>("cameraPosition");
				if (cameraPosition != nullval)
					*cameraPosition = camera->GetPosition();

				// TODO - remove this hack. We need to do something to send data such as this in uniform way.
				auto time = shader->TryGetProperty<float>("time");
				if (time != nullval)
					*time = 0;

				// Sends data to GPU if changed
				shader->Apply();

				// Render
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
