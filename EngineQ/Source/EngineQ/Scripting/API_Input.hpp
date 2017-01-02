#ifndef ENGINEQ_SCRIPTING_API_INPUT_HPP
#define ENGINEQ_SCRIPTING_API_INPUT_HPP

// This project
#include "Types.hpp"
#include "EngineQ/Systems/InputController.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_Input
		{
		public:
			static void API_KeyPressed(InputController::Key keyCode, bool& result);
			static void API_MouseButtonDown(InputController::MouseButton buttonCode, bool& result);
			static void API_MousePosition(Math::Vector2& position);
			static void API_MouseDeltaPosition(Math::Vector2& deltaPosition);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif