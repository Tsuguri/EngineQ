#include <algorithm>

#include "InputController.hpp"
#include <GLFW/glfw3.h>

EngineQ::InputController::InputController()
{
	std::fill_n(keys, 512, false);
	std::fill_n(mouseButtons, 10, false);
}

void EngineQ::InputController::KeyAction(int key, int scancode, int action, int mode)
{
	if(action==GLFW_PRESS)
	{
		keys[key] = true;
	}
	if(action==GLFW_RELEASE)
	{
		keys[key] = false;
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
}

void EngineQ::InputController::MouseMoveAction(double xpos, double ypos)
{
	Math::Vector2 tmp{ static_cast<float>(xpos),static_cast<float>(ypos) };
	cursorDeltaPos = tmp - cursorPos;
	cursorPos = tmp;
}

bool EngineQ::InputController::isButtonDown(int keyCode)
{
	if (keyCode < 0 || keyCode>=1024)
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
