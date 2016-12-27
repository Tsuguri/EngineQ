#ifndef ENGINEQ_GRAPHICS_IMPLEMENTATION_SCREENDATAPROVIDER
#define ENGINEQ_GRAPHICS_IMPLEMENTATION_SCREENDATAPROVIDER

// Standard

// Other projects

#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"

// This project

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			class ScreenDataProvider : public Graphics::ScreenDataProvider
			{
			public:
				Math::Vector2i screenSize = Math::Vector2i{ 0, 0 };

				virtual Math::Vector2i GetScreenSize() const;

				void SetScreenSize(Math::Vector2i size);
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_IMPLEMENTATION_SCREENDATAPROVIDER
