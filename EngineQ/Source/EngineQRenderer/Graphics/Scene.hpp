#ifndef ENGINEQ_GRAPHICS_SCENE_HPP
#define ENGINEQ_GRAPHICS_SCENE_HPP

// This project
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Shadows/Light.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class Scene
		{
		public:
			virtual Camera* GetActiveCamera() const=0 ;
			virtual const std::vector<Renderable*>& GetRenderables() const=0;
			virtual const std::vector<Shadows::Light*>& GetLights() const = 0;
		};
	}
}

#endif
