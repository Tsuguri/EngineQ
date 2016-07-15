#include <algorithm>

#include <GLFW/glfw3.h>
#include <mono/metadata/debug-helpers.h>

#include "InputController.hpp"
#include "Scripting/ScriptEngine.hpp"

EngineQ::InputController::InputController()
{
	std::fill_n(keys, 512, false);
	std::fill_n(mouseButtons, 10, false);
}

void EngineQ::InputController::InitMethods(Scripting::ScriptEngine* se)
{
	this->se = se;
	keyEventMethod = se->GetInputMethod(":KeyEvent");
	mouseButtonEventMethod = se->GetInputMethod(":MouseButtonEvent");
}

void EngineQ::InputController::KeyAction(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}

	if (keyEventMethod != nullptr)
	{
		void* args[2];
		int k = key;
		int a = action;
		args[0] = static_cast<void*>(&k);
		args[1] = static_cast<void*>(&a);
		se->InvokeStaticMethod(keyEventMethod, args);
	}
}

void EngineQ::InputController::MouseButtonAction(int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		mouseButtons[button] = true;
	}
	if (action == GLFW_RELEASE)
	{
		mouseButtons[button] = false;
	}
	if (mouseButtonEventMethod != nullptr)
	{
		void* args[2];
		int k = button;
		int a = action;
		args[0] = static_cast<void*>(&k);
		args[1] = static_cast<void*>(&a);
		se->InvokeStaticMethod(mouseButtonEventMethod, args);
	}
}

void EngineQ::InputController::MouseMoveAction(double xpos, double ypos)
{
	Math::Vector2 tmp{ static_cast<float>(xpos),static_cast<float>(ypos) };
	cursorDeltaPos = tmp - cursorPos;
	cursorPos = tmp;
}

void EngineQ::InputController::InvokeSEEvent(int key, int action)
{
	auto p = mono_method_desc_new("EgineQ.Input.KeyPressedEvent(Key key)", true);

}

bool EngineQ::InputController::isButtonDown(int keyCode)
{
	if (keyCode < 0 || keyCode >= 1024)
		throw "key not in range";
	return keys[keyCode];
}

bool EngineQ::InputController::isMouseButtonDown(int keyCode)
{

	if (keyCode < 0 || keyCode >= 10)
		throw "key not in range";
	return mouseButtons[keyCode];
}

EngineQ::Math::Vector2 EngineQ::InputController::GetMousePosition() const
{
	return cursorPos;
}
