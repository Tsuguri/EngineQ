#ifndef ENGINEQ_GRAPGICS_SCREEN_DATA_PROVIDER_HPP
#define ENGINEQ_GRAPGICS_SCREEN_DATA_PROVIDER_HPP

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
			Utilities::Event<ScreenDataProvider, void(Math::Vector2i)> ResizeEvent;

			virtual Math::Vector2i GetScreenSize() const = 0;

		protected:
			bool ResizeEventIsEmpty();
			void ResizeEventInvoke(Math::Vector2i size);
		};
	}
}

#endif // !ENGINEQ_GRAPGICS_SCREEN_DATA_PROVIDER_HPP
