#include "API_Input.hpp"

void EngineQ::Scripting::API_Input::API_KeyPresed(int keyCode, bool& result)
{
	result = Engine::Get()->input.isButtonDown(keyCode);
}

void EngineQ::Scripting::API_Input::API_MouseButtonDown(int buttonCode, bool& result)
{
	result = Engine::Get()->input.isMouseButtonDown(buttonCode);
}

void EngineQ::Scripting::API_Input::API_MousePosition(Math::Vector2& position)
{
	position = Engine::Get()->input.GetMousePosition();
}

void EngineQ::Scripting::API_Input::API_Register(ScriptEngine& scriptEngine)
{
	scriptEngine.API_Register("EngineQ.Input::API_KeyPressed",API_KeyPresed);
	scriptEngine.API_Register("EngineQ.Input::API_MouseButtonDown", API_MouseButtonDown);
	scriptEngine.API_Register("EngineQ.Input::API_MousePosition", API_MousePosition);

}
