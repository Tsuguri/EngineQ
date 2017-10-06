#include "Renderer.hpp"

// Libraries
#include <GL/glew.h>

// This project
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

		void Renderer::SetGlobalShadows(bool state)
		{
			globalShadows = state;
		}

		void Renderer::Render(Scene& scene, ScreenDataProvider* dataProvider)
		{
			const auto& renderables = scene.GetRenderables();

			auto& lights = scene.GetLights();

			// If shadows are enabled - render depthmaps into textures
			if (globalShadows)
			{
				std::size_t index = 0;
				for (auto light : lights)
				{
					this->OnBeforeLightRender(index);
					light->RenderDepthMap(renderables);
					this->OnAfterLightRender(index);

					index += 1;
				}
			}


			this->OnBeforeRender();

			// Render target binding
			if (this->framebuffer == nullptr)
				// Binds default buffer - screen
				Framebuffer::BindDefault();
			else
				this->framebuffer->Bind();

			// Render target color buffer and depth buffer clearing:
			auto size = dataProvider->GetScreenSize();

			glViewport(0, 0, size.X, size.Y);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Rendering from scene active camera pointview 
			auto camera = scene.GetActiveCamera();

			// Renders each object from vector get from scene

			// Wireframe
		//	glDisable(GL_CULL_FACE);
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			for (auto renderable : scene.GetRenderables())
			{
				auto mesh = renderable->GetMesh();

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

				if (globalShadows && !deferred)
				{
					// set shadow matrices

					//sets input textures in samplers
				}


				// Sends data to GPU if changed
				shader->Apply();

				// Render
				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
			}

			// Wireframe
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//	glEnable(GL_CULL_FACE);

			this->OnAfterRender();
		}

		void Renderer::SetTargetBuffer(std::shared_ptr<Framebuffer> buffer)
		{
			framebuffer = buffer;
		}

		void Renderer::OnBeforeRender()
		{
		}

		void Renderer::OnAfterRender()
		{
		}

		void Renderer::OnBeforeLightRender(std::size_t lightIndex) 
		{
		}

		void Renderer::OnAfterLightRender(std::size_t lightIndex)
		{
		}

		RendererFactory::~RendererFactory()
		{
		}

		std::unique_ptr<Renderer> RendererFactory::CreateRenderer()
		{
			return std::make_unique<Renderer>();
		}
}
}
