#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include "../Scene.hpp"
#include "Framebuffer.hpp"
#include "Renderer.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		class Renderer
		{
		private:
			bool deferred;
			std::shared_ptr<Framebuffer> framebuffer;

			Shader* (Renderable::*shaderMethod)() const;

		public:
			void SetDeferred(bool state);
			void Render(Scene* scene) const;
			void SetTargetBuffer(std::shared_ptr<Framebuffer> buffer);


		};
	}
}

#endif
