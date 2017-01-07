#include "ScreenDataProvider.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		bool ScreenDataProvider::ResizeEventIsEmpty() 
		{ 
			return ResizeEvent.IsEmpty(); 
		}

		void ScreenDataProvider::ResizeEventInvoke(Math::Vector2i size) 
		{ 
			ResizeEvent.Invoke(size); 
		}
	}
}