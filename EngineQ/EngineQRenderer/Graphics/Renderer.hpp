#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include <memory>

#include "Types.hpp"

#include "Renderable.hpp"
#include "Utils\ScreenDataProvider.hpp"

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

		public:
			void SetDeferred(bool state);
			void SetGlobalShadows(bool state);
			void Render(Scene& scene, ScreenDataProvider* dataProvider) const;
			void SetTargetBuffer(std::shared_ptr<Framebuffer> buffer);
		};
	}
}

#endif
