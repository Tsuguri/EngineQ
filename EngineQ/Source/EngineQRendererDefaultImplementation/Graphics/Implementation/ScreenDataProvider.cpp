#include "ScreenDataProvider.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			Math::Vector2i ScreenDataProvider::GetScreenSize() const
			{
				return screenSize;
			}

			void ScreenDataProvider::SetScreenSize(Math::Vector2i size)
			{
				if (screenSize != size)
				{
					screenSize = size;
					ResizeEventInvoke(size.X, size.Y);
				}
			}

		}
	}
}