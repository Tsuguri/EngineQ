#pragma once

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQCommon/Utilities/Event.hpp"


namespace EngineQ
{
	namespace Graphics
	{
			class ScreenDataProvider
			{
			public:
				Utilities::Event<ScreenDataProvider, void(int, int)> resizeEvent;

				virtual Math::Vector2i GetScreenSize() const = 0;

			protected:
				bool ResizeEventIsEmpty() { return resizeEvent.IsEmpty(); }
				void ResizeEventInvoke(int width, int height) { resizeEvent.Invoke(width, height); }
			};
	}
}