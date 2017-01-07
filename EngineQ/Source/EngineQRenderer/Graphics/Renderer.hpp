#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

// Standard includes
#include <memory>

// This project
#include "Types.hpp"
#include "Renderable.hpp"
#include "Utils/ScreenDataProvider.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class Renderer
		{
		private:
			bool deferred = false;
			bool globalShadows = false;
			std::shared_ptr<Framebuffer> framebuffer = nullptr;

			Graphics::ShaderProperties* (Graphics::Renderable::*shaderMethod)() const = &Graphics::Renderable::GetDeferredShader;

		protected:
			virtual void OnBeforeRender();
			virtual void OnAfterRender();

			virtual void OnBeforeLightRender(std::size_t lightIndex);
			virtual void OnAfterLightRender(std::size_t lightIndex);

		public:
			virtual ~Renderer() = default;

			void SetDeferred(bool state);
			void SetGlobalShadows(bool state);
			void Render(Scene& scene, ScreenDataProvider* dataProvider);
			void SetTargetBuffer(std::shared_ptr<Framebuffer> buffer);
		};

		class RendererFactory
		{
		public:
			virtual ~RendererFactory();

			virtual std::unique_ptr<Renderer> CreateRenderer();
		};
	}
}

#endif
