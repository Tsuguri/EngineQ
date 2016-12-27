#ifndef ENGINEQ_GRAPHICS_IMPLEMENTATION_SCENE
#define ENGINEQ_GRAPHICS_IMPLEMENTATION_SCENE

// Standard
#include <vector>

// Other projects

#include "EngineQRenderer/Graphics/Scene.hpp"

// This project

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			class Scene : public Graphics::Scene
			{
			public:
				std::vector<Graphics::Renderable*> renderables;
				std::vector<Graphics::Shadows::Light*> lights;
				Graphics::Camera* activeCamera;

				Graphics::Camera* GetActiveCamera() const override;

				const std::vector<Graphics::Shadows::Light*>& GetLights() const override;

				const std::vector<Graphics::Renderable*>& GetRenderables() const override;

			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_IMPLEMENTATION_SCENE
