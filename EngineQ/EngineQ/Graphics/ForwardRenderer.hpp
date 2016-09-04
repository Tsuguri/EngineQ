#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include "../Scene.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		class ForwardRenderer
		{
		private:

		public:
			ForwardRenderer();
			virtual ~ForwardRenderer();

			void Render(Scene* scene);


		};
	}
}

#endif
