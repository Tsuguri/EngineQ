#ifndef ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP

// Standard includes
#include <memory>

// This project
#include "EngineQRenderer/Graphics/Texture.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class ShadowCaster
			{
			public:

				std::shared_ptr<Texture> texture;
				float farPlane;

				virtual void Initialize() = 0;
				virtual void Render(Renderable* renderable) = 0;

			};
		}
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP
