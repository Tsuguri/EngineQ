#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include "../Scene.hpp"
#include "Framebuffer.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		class ForwardRenderer
		{
		private:
			Framebuffer* framebuffer=nullptr;
		public:
			ForwardRenderer();
			virtual ~ForwardRenderer();

			void Render(Scene* scene);
			void SetTargetBuffer(Framebuffer* buffer);


		};
	}
}

#endif
