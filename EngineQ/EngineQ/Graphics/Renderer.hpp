#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include <memory>

#include "Types.hpp"
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Renderer
		{
		private:
			bool deferred;
			std::shared_ptr<Framebuffer> framebuffer;

			ShaderProperties* (Renderable::*shaderMethod)() const;

		public:
			void SetDeferred(bool state);
			void Render(Scene* scene) const;
			void SetTargetBuffer(std::shared_ptr<Framebuffer> buffer);
		};
	}
}

#endif
