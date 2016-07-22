#include <algorithm>

#include <GLFW/glfw3.h>

#include "InputController.hpp"
#include "Scripting/ScriptEngine.hpp"

EngineQ::InputController::InputController()
{
	std::fill_n(keys, 128, false);
	std::fill_n(mouseButtons, 10, false);
	SetTranslateTable();
}

void EngineQ::InputController::InitMethods(Scripting::ScriptEngine* se)
{
	this->se = se;
	keyEventMethod = se->GetInputMethod(":KeyEvent");
	mouseButtonEventMethod = se->GetInputMethod(":MouseButtonEvent");
}

void EngineQ::InputController::KeyAction(int key, int scancode, int action, int mode)
{
	key = translateTable[key];

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

void EngineQ::InputController::SetTranslateTable()
{

	translateTable[GLFW_KEY_SPACE] = Space;
	translateTable[GLFW_KEY_APOSTROPHE] = Apostrophe;
	translateTable[GLFW_KEY_COMMA] = Comma;
	translateTable[GLFW_KEY_MINUS] = Minus;
	translateTable[GLFW_KEY_PERIOD] = Period;
	translateTable[GLFW_KEY_SLASH] = Slash;
	translateTable[GLFW_KEY_0] = N0;
	translateTable[GLFW_KEY_1] = N1;
	translateTable[GLFW_KEY_2] = N2;
	translateTable[GLFW_KEY_3] = N3;
	translateTable[GLFW_KEY_4] = N4;
	translateTable[GLFW_KEY_5] = N5;
	translateTable[GLFW_KEY_6] = N6;
	translateTable[GLFW_KEY_7] = N7;
	translateTable[GLFW_KEY_8] = N8;
	translateTable[GLFW_KEY_9] = N9;
	translateTable[GLFW_KEY_SEMICOLON] = Semicolon;
	translateTable[GLFW_KEY_EQUAL] = Equal;
	translateTable[GLFW_KEY_A] = A;
	translateTable[GLFW_KEY_B] = B;
	translateTable[GLFW_KEY_C] = C;
	translateTable[GLFW_KEY_D] = D;
	translateTable[GLFW_KEY_E] = E;
	translateTable[GLFW_KEY_F] = F;
	translateTable[GLFW_KEY_G] = G;
	translateTable[GLFW_KEY_H] = H;
	translateTable[GLFW_KEY_I] = I;
	translateTable[GLFW_KEY_J] = J;
	translateTable[GLFW_KEY_K] = K;
	translateTable[GLFW_KEY_L] = L;
	translateTable[GLFW_KEY_M] = M;
	translateTable[GLFW_KEY_N] = N;
	translateTable[GLFW_KEY_O] = O;
	translateTable[GLFW_KEY_P] = P;
	translateTable[GLFW_KEY_Q] = Q;
	translateTable[GLFW_KEY_R] = R;
	translateTable[GLFW_KEY_S] = S;
	translateTable[GLFW_KEY_T] = T;
	translateTable[GLFW_KEY_U] = U;
	translateTable[GLFW_KEY_V] = V;
	translateTable[GLFW_KEY_W] = W;
	translateTable[GLFW_KEY_X] = X;
	translateTable[GLFW_KEY_Y] = Y;
	translateTable[GLFW_KEY_Z] = Z;
	translateTable[GLFW_KEY_LEFT_BRACKET] = LeftBracket;
	translateTable[GLFW_KEY_BACKSLASH] = Backslash;
	translateTable[GLFW_KEY_RIGHT_BRACKET] = RightBracket;
	translateTable[GLFW_KEY_GRAVE_ACCENT] = GraveAccent;
	translateTable[GLFW_KEY_WORLD_1] = World1;
	translateTable[GLFW_KEY_WORLD_2] = World2;
	translateTable[GLFW_KEY_ESCAPE] = Escape;
	translateTable[GLFW_KEY_ENTER] = Enter;
	translateTable[GLFW_KEY_TAB] = Tab;
	translateTable[GLFW_KEY_BACKSLASH] = Backslash;
	translateTable[GLFW_KEY_INSERT] = Insert;
	translateTable[GLFW_KEY_DELETE] = Delete;
	translateTable[GLFW_KEY_RIGHT] = Right;
	translateTable[GLFW_KEY_LEFT] = Left;
	translateTable[GLFW_KEY_DOWN] = Down;
	translateTable[GLFW_KEY_UP] = Up;
	translateTable[GLFW_KEY_PAGE_UP] = PageUp;
	translateTable[GLFW_KEY_PAGE_DOWN] = PageDown;
	translateTable[GLFW_KEY_HOME] = Home;
	translateTable[GLFW_KEY_END] = End;
	translateTable[GLFW_KEY_CAPS_LOCK] = CapsLock;
	translateTable[GLFW_KEY_SCROLL_LOCK] = ScrollLock;
	translateTable[GLFW_KEY_NUM_LOCK] = NumLock;
	translateTable[GLFW_KEY_PRINT_SCREEN] = PrintScreen;
	translateTable[GLFW_KEY_PAUSE] = Pause;
	translateTable[GLFW_KEY_F1] = F1;
	translateTable[GLFW_KEY_F2] = F2;
	translateTable[GLFW_KEY_F3] = F3;
	translateTable[GLFW_KEY_F4] = F4;
	translateTable[GLFW_KEY_F5] = F5;
	translateTable[GLFW_KEY_F6] = F6;
	translateTable[GLFW_KEY_F7] = F7;
	translateTable[GLFW_KEY_F8] = F8;
	translateTable[GLFW_KEY_F9] = F9;
	translateTable[GLFW_KEY_F10] = F10;
	translateTable[GLFW_KEY_F11] = F11;
	translateTable[GLFW_KEY_F12] = F12;
	translateTable[GLFW_KEY_F13] = F13;
	translateTable[GLFW_KEY_F14] = F14;
	translateTable[GLFW_KEY_F15] = F15;
	translateTable[GLFW_KEY_F16] = F16;
	translateTable[GLFW_KEY_F17] = F17;
	translateTable[GLFW_KEY_F18] = F18;
	translateTable[GLFW_KEY_F19] = F19;
	translateTable[GLFW_KEY_F20] = F20;
	translateTable[GLFW_KEY_F21] = F21;
	translateTable[GLFW_KEY_F22] = F22;
	translateTable[GLFW_KEY_F23] = F23;
	translateTable[GLFW_KEY_F24] = F24;
	translateTable[GLFW_KEY_F25] = F25;
	translateTable[GLFW_KEY_KP_0] = Kp0;
	translateTable[GLFW_KEY_KP_1] = Kp1;
	translateTable[GLFW_KEY_KP_2] = Kp2;
	translateTable[GLFW_KEY_KP_3] = Kp3;
	translateTable[GLFW_KEY_KP_4] = Kp4;
	translateTable[GLFW_KEY_KP_5] = Kp5;
	translateTable[GLFW_KEY_KP_6] = Kp6;
	translateTable[GLFW_KEY_KP_7] = Kp7;
	translateTable[GLFW_KEY_KP_8] = Kp8;
	translateTable[GLFW_KEY_KP_9] = Kp9;
	translateTable[GLFW_KEY_KP_DECIMAL] = KpDecimal;
	translateTable[GLFW_KEY_KP_DIVIDE] = KpDivide;
	translateTable[GLFW_KEY_KP_MULTIPLY] = KpMultiply;
	translateTable[GLFW_KEY_KP_SUBTRACT] = KpSubtract;
	translateTable[GLFW_KEY_KP_ADD] = KpAdd;
	translateTable[GLFW_KEY_KP_ENTER] = Enter;
	translateTable[GLFW_KEY_KP_EQUAL] = Equal;
	translateTable[GLFW_KEY_LEFT_SHIFT] = LeftShift;
	translateTable[GLFW_KEY_LEFT_CONTROL] = LeftControl;
	translateTable[GLFW_KEY_LEFT_ALT] = LeftAlt;
	translateTable[GLFW_KEY_LEFT_SUPER] = LeftSuper;
	translateTable[GLFW_KEY_RIGHT_SHIFT] = RightShift;
	translateTable[GLFW_KEY_RIGHT_CONTROL] = RightControl;
	translateTable[GLFW_KEY_RIGHT_ALT] = RightAlt;
	translateTable[GLFW_KEY_RIGHT_SUPER] = RightSuper;
	translateTable[GLFW_KEY_MENU] = Menu;
}

bool EngineQ::InputController::isButtonDown(Key keyCode)
{
	if (keyCode < 0 || keyCode >= 119)
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

EngineQ::Math::Vector2 EngineQ::InputController::GetMouseDeltaPosition() const
{
	return cursorDeltaPos;
}

void EngineQ::InputController::ClearDelta()
{
	cursorDeltaPos = Math::Vector2(0);
}
