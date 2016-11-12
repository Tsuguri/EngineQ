#pragma once

#include <Math\Vector2.hpp>
namespace EngineQ
{
	namespace Graphics {

		class ScreenDataProvider
		{
		public:
			Utilities::Event<ScreenDataProvider, void(int, int)> resizeEvent;

			virtual Math::Vector2i GetScreenSize()=0;

		protected:
			bool ResizeEventIsEmpty() { return resizeEvent.IsEmpty(); }
			void ResizeEventInvoke(int width, int height) { resizeEvent.Invoke(width,height); }
		};
	}
}