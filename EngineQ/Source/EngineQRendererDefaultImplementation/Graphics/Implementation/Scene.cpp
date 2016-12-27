#include "Scene.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{

			Graphics::Camera* Scene::GetActiveCamera() const
			{
				return activeCamera;
			}


			const std::vector<Graphics::Shadows::Light*>& Scene::GetLights() const
			{
				return lights;
			}

			const std::vector<Graphics::Renderable*>& Scene::GetRenderables() const
			{
				return renderables;
			}
		}
	}
}