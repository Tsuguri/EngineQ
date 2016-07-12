#ifndef ENGINEQ_FORWARDRENDERER_HPP
#define ENGINEQ_FORWARDRENDERER_HPP

#include "Scene.hpp"
#include "Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		class ForwardRenderer
		{
		private:

		public:
			ForwardRenderer();
			~ForwardRenderer();

			void Render(Scene* scene);


		};
	}
}

#endif
