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
			std::shared_ptr<Framebuffer> framebuffer;
		public:
			ForwardRenderer();
			virtual ~ForwardRenderer();

			void Render(Scene* scene);
			void SetTargetBuffer(std::shared_ptr<Framebuffer> buffer);


		};
	}
}

#endif
