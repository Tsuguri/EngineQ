#ifndef ENGINEQ_GRAPHICS_SCENE_HPP
#define ENGINEQ_GRAPHICS_SCENE_HPP


#include "Camera.hpp"
#include "Renderable.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Scene
		{
		public:
			virtual Camera* GetActiveCamera() const=0 ;
			virtual const std::vector<Renderable*>& GetRenderables() const=0;
		};
	}
}

#endif
