#include "API_Input.hpp"

#include "ScriptEngine.hpp"

#include "../Engine.hpp"

void EngineQ::Scripting::API_Input::API_KeyPressed(InputController::Key keyCode, bool& result)
{
	result = Engine::Get().input.IsButtonDown(keyCode);
}

void EngineQ::Scripting::API_Input::API_MouseButtonDown(InputController::MouseButton buttonCode, bool& result)
{
	result = Engine::Get().input.IsMouseButtonDown(buttonCode);
}

void EngineQ::Scripting::API_Input::API_MousePosition(Math::Vector2& position)
{
	position = Engine::Get().input.GetMousePosition();
}

void EngineQ::Scripting::API_Input::API_MouseDeltaPosition(Math::Vector2& deltaPosition)
{
	deltaPosition = Engine::Get().input.GetMouseDeltaPosition();
}

void EngineQ::Scripting::API_Input::API_Register(ScriptEngine& scriptEngine)
{
	scriptEngine.API_Register("EngineQ.Input::API_KeyPressed", API_KeyPressed);
	scriptEngine.API_Register("EngineQ.Input::API_MouseButtonDown", API_MouseButtonDown);
	scriptEngine.API_Register("EngineQ.Input::API_MousePosition", API_MousePosition);
	scriptEngine.API_Register("EngineQ.Input::API_MouseDeltaPosition", API_MouseDeltaPosition);

}
