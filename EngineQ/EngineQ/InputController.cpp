#include "InputController.hpp"

// Standard includes
#include <algorithm>

// Libraries
#include <GLFW/glfw3.h>

// This project
#include "Scripting/ScriptEngine.hpp"


namespace EngineQ
{
	InputController::Key keysTranslateTable[GLFW_KEY_LAST + 1] = { InputController::Key::Unknown };
	InputController::MouseButton mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_LAST + 1] = { InputController::MouseButton::Unknown };

	void InputController::SetTranslateTables()
	{
		keysTranslateTable[GLFW_KEY_SPACE] = Key::Space;
		keysTranslateTable[GLFW_KEY_APOSTROPHE] = Key::Apostrophe;
		keysTranslateTable[GLFW_KEY_COMMA] = Key::Comma;
		keysTranslateTable[GLFW_KEY_MINUS] = Key::Minus;
		keysTranslateTable[GLFW_KEY_PERIOD] = Key::Period;
		keysTranslateTable[GLFW_KEY_SLASH] = Key::Slash;
		keysTranslateTable[GLFW_KEY_0] = Key::N0;
		keysTranslateTable[GLFW_KEY_1] = Key::N1;
		keysTranslateTable[GLFW_KEY_2] = Key::N2;
		keysTranslateTable[GLFW_KEY_3] = Key::N3;
		keysTranslateTable[GLFW_KEY_4] = Key::N4;
		keysTranslateTable[GLFW_KEY_5] = Key::N5;
		keysTranslateTable[GLFW_KEY_6] = Key::N6;
		keysTranslateTable[GLFW_KEY_7] = Key::N7;
		keysTranslateTable[GLFW_KEY_8] = Key::N8;
		keysTranslateTable[GLFW_KEY_9] = Key::N9;
		keysTranslateTable[GLFW_KEY_SEMICOLON] = Key::Semicolon;
		keysTranslateTable[GLFW_KEY_EQUAL] = Key::Equal;
		keysTranslateTable[GLFW_KEY_A] = Key::A;
		keysTranslateTable[GLFW_KEY_B] = Key::B;
		keysTranslateTable[GLFW_KEY_C] = Key::C;
		keysTranslateTable[GLFW_KEY_D] = Key::D;
		keysTranslateTable[GLFW_KEY_E] = Key::E;
		keysTranslateTable[GLFW_KEY_F] = Key::F;
		keysTranslateTable[GLFW_KEY_G] = Key::G;
		keysTranslateTable[GLFW_KEY_H] = Key::H;
		keysTranslateTable[GLFW_KEY_I] = Key::I;
		keysTranslateTable[GLFW_KEY_J] = Key::J;
		keysTranslateTable[GLFW_KEY_K] = Key::K;
		keysTranslateTable[GLFW_KEY_L] = Key::L;
		keysTranslateTable[GLFW_KEY_M] = Key::M;
		keysTranslateTable[GLFW_KEY_N] = Key::N;
		keysTranslateTable[GLFW_KEY_O] = Key::O;
		keysTranslateTable[GLFW_KEY_P] = Key::P;
		keysTranslateTable[GLFW_KEY_Q] = Key::Q;
		keysTranslateTable[GLFW_KEY_R] = Key::R;
		keysTranslateTable[GLFW_KEY_S] = Key::S;
		keysTranslateTable[GLFW_KEY_T] = Key::T;
		keysTranslateTable[GLFW_KEY_U] = Key::U;
		keysTranslateTable[GLFW_KEY_V] = Key::V;
		keysTranslateTable[GLFW_KEY_W] = Key::W;
		keysTranslateTable[GLFW_KEY_X] = Key::X;
		keysTranslateTable[GLFW_KEY_Y] = Key::Y;
		keysTranslateTable[GLFW_KEY_Z] = Key::Z;
		keysTranslateTable[GLFW_KEY_LEFT_BRACKET] = Key::LeftBracket;
		keysTranslateTable[GLFW_KEY_BACKSLASH] = Key::Backslash;
		keysTranslateTable[GLFW_KEY_RIGHT_BRACKET] = Key::RightBracket;
		keysTranslateTable[GLFW_KEY_GRAVE_ACCENT] = Key::GraveAccent;
		keysTranslateTable[GLFW_KEY_WORLD_1] = Key::World1;
		keysTranslateTable[GLFW_KEY_WORLD_2] = Key::World2;
		keysTranslateTable[GLFW_KEY_ESCAPE] = Key::Escape;
		keysTranslateTable[GLFW_KEY_ENTER] = Key::Enter;
		keysTranslateTable[GLFW_KEY_TAB] = Key::Tab;
		keysTranslateTable[GLFW_KEY_BACKSLASH] = Key::Backslash;
		keysTranslateTable[GLFW_KEY_INSERT] = Key::Insert;
		keysTranslateTable[GLFW_KEY_DELETE] = Key::Delete;
		keysTranslateTable[GLFW_KEY_RIGHT] = Key::Right;
		keysTranslateTable[GLFW_KEY_LEFT] = Key::Left;
		keysTranslateTable[GLFW_KEY_DOWN] = Key::Down;
		keysTranslateTable[GLFW_KEY_UP] = Key::Up;
		keysTranslateTable[GLFW_KEY_PAGE_UP] = Key::PageUp;
		keysTranslateTable[GLFW_KEY_PAGE_DOWN] = Key::PageDown;
		keysTranslateTable[GLFW_KEY_HOME] = Key::Home;
		keysTranslateTable[GLFW_KEY_END] = Key::End;
		keysTranslateTable[GLFW_KEY_CAPS_LOCK] = Key::CapsLock;
		keysTranslateTable[GLFW_KEY_SCROLL_LOCK] = Key::ScrollLock;
		keysTranslateTable[GLFW_KEY_NUM_LOCK] = Key::NumLock;
		keysTranslateTable[GLFW_KEY_PRINT_SCREEN] = Key::PrintScreen;
		keysTranslateTable[GLFW_KEY_PAUSE] = Key::Pause;
		keysTranslateTable[GLFW_KEY_F1] = Key::F1;
		keysTranslateTable[GLFW_KEY_F2] = Key::F2;
		keysTranslateTable[GLFW_KEY_F3] = Key::F3;
		keysTranslateTable[GLFW_KEY_F4] = Key::F4;
		keysTranslateTable[GLFW_KEY_F5] = Key::F5;
		keysTranslateTable[GLFW_KEY_F6] = Key::F6;
		keysTranslateTable[GLFW_KEY_F7] = Key::F7;
		keysTranslateTable[GLFW_KEY_F8] = Key::F8;
		keysTranslateTable[GLFW_KEY_F9] = Key::F9;
		keysTranslateTable[GLFW_KEY_F10] = Key::F10;
		keysTranslateTable[GLFW_KEY_F11] = Key::F11;
		keysTranslateTable[GLFW_KEY_F12] = Key::F12;
		keysTranslateTable[GLFW_KEY_F13] = Key::F13;
		keysTranslateTable[GLFW_KEY_F14] = Key::F14;
		keysTranslateTable[GLFW_KEY_F15] = Key::F15;
		keysTranslateTable[GLFW_KEY_F16] = Key::F16;
		keysTranslateTable[GLFW_KEY_F17] = Key::F17;
		keysTranslateTable[GLFW_KEY_F18] = Key::F18;
		keysTranslateTable[GLFW_KEY_F19] = Key::F19;
		keysTranslateTable[GLFW_KEY_F20] = Key::F20;
		keysTranslateTable[GLFW_KEY_F21] = Key::F21;
		keysTranslateTable[GLFW_KEY_F22] = Key::F22;
		keysTranslateTable[GLFW_KEY_F23] = Key::F23;
		keysTranslateTable[GLFW_KEY_F24] = Key::F24;
		keysTranslateTable[GLFW_KEY_F25] = Key::F25;
		keysTranslateTable[GLFW_KEY_KP_0] = Key::Kp0;
		keysTranslateTable[GLFW_KEY_KP_1] = Key::Kp1;
		keysTranslateTable[GLFW_KEY_KP_2] = Key::Kp2;
		keysTranslateTable[GLFW_KEY_KP_3] = Key::Kp3;
		keysTranslateTable[GLFW_KEY_KP_4] = Key::Kp4;
		keysTranslateTable[GLFW_KEY_KP_5] = Key::Kp5;
		keysTranslateTable[GLFW_KEY_KP_6] = Key::Kp6;
		keysTranslateTable[GLFW_KEY_KP_7] = Key::Kp7;
		keysTranslateTable[GLFW_KEY_KP_8] = Key::Kp8;
		keysTranslateTable[GLFW_KEY_KP_9] = Key::Kp9;
		keysTranslateTable[GLFW_KEY_KP_DECIMAL] = Key::KpDecimal;
		keysTranslateTable[GLFW_KEY_KP_DIVIDE] = Key::KpDivide;
		keysTranslateTable[GLFW_KEY_KP_MULTIPLY] = Key::KpMultiply;
		keysTranslateTable[GLFW_KEY_KP_SUBTRACT] = Key::KpSubtract;
		keysTranslateTable[GLFW_KEY_KP_ADD] = Key::KpAdd;
		keysTranslateTable[GLFW_KEY_KP_ENTER] = Key::Enter;
		keysTranslateTable[GLFW_KEY_KP_EQUAL] = Key::Equal;
		keysTranslateTable[GLFW_KEY_LEFT_SHIFT] = Key::LeftShift;
		keysTranslateTable[GLFW_KEY_LEFT_CONTROL] = Key::LeftControl;
		keysTranslateTable[GLFW_KEY_LEFT_ALT] = Key::LeftAlt;
		keysTranslateTable[GLFW_KEY_LEFT_SUPER] = Key::LeftSuper;
		keysTranslateTable[GLFW_KEY_RIGHT_SHIFT] = Key::RightShift;
		keysTranslateTable[GLFW_KEY_RIGHT_CONTROL] = Key::RightControl;
		keysTranslateTable[GLFW_KEY_RIGHT_ALT] = Key::RightAlt;
		keysTranslateTable[GLFW_KEY_RIGHT_SUPER] = Key::RightSuper;
		keysTranslateTable[GLFW_KEY_MENU] = Key::Menu;

		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_LEFT] = MouseButton::Left;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_RIGHT] = MouseButton::Right;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_MIDDLE] = MouseButton::Middle;

		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_4] = MouseButton::Button4;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_5] = MouseButton::Button5;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_6] = MouseButton::Button6;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_7] = MouseButton::Button7;
		mouseButtonsTranslateTable[GLFW_MOUSE_BUTTON_8] = MouseButton::Button8;
	}

	InputController::Initializer::Initializer()
	{
		InputController::SetTranslateTables();
	}
	
	InputController::Initializer InputController::initializer;




	void InputController::InitMethods(Scripting::ScriptEngine* se)
	{
		this->se = se;
		keyEventMethod = se->GetInputMethod(":KeyEvent");
		mouseButtonEventMethod = se->GetInputMethod(":MouseButtonEvent");
	}

	void InputController::KeyAction(int key, int scancode, int action, int mode)
	{
		key = static_cast<int>(keysTranslateTable[key]);

		switch (action)
		{
			case GLFW_PRESS:
			keys[key] = true;
			action = static_cast<int>(KeyAction::Press);
			break;

			case GLFW_RELEASE:
			keys[key] = false;
			action = static_cast<int>(KeyAction::Release);
			break;

			case GLFW_REPEAT:
			action = static_cast<int>(KeyAction::Repeat);
			break;

			default:
			action = static_cast<int>(KeyAction::Unknown);
			break;
		}

		if (keyEventMethod != nullptr)
		{
			void* args[2];
			args[0] = static_cast<void*>(&key);
			args[1] = static_cast<void*>(&action);
			se->InvokeStaticMethod(keyEventMethod, args);
		}
	}

	void InputController::MouseButtonAction(int button, int action, int mode)
	{
		button = static_cast<int>(mouseButtonsTranslateTable[button]);

		switch (action)
		{
			case GLFW_PRESS:
			mouseButtons[button] = true;
			action = static_cast<int>(KeyAction::Press);
			break;

			case GLFW_RELEASE:
			mouseButtons[button] = false;
			action = static_cast<int>(KeyAction::Release);
			break;

			case GLFW_REPEAT:
			action = static_cast<int>(KeyAction::Repeat);
			break;

			default:
			action = static_cast<int>(KeyAction::Unknown);
			break;
		}

		if (mouseButtonEventMethod != nullptr)
		{
			void* args[2];
			args[0] = static_cast<void*>(&button);
			args[1] = static_cast<void*>(&action);
			se->InvokeStaticMethod(mouseButtonEventMethod, args);
		}
	}

	void InputController::MouseMoveAction(double xpos, double ypos)
	{
		Math::Vector2 tmp{ static_cast<float>(xpos), static_cast<float>(ypos) };
		cursorDeltaPos = tmp - cursorPos;
		cursorPos = tmp;
	}

	bool InputController::IsButtonDown(Key keyCode)
	{
		if (keyCode < static_cast<Key>(0) || keyCode >= Key::Count)
			throw "key not in range";

		return keys[static_cast<int>(keyCode)];
	}

	bool InputController::IsMouseButtonDown(MouseButton keyCode)
	{
		if (keyCode < static_cast<MouseButton>(0) || keyCode >= MouseButton::Count)
			throw "key not in range";

		return mouseButtons[static_cast<int>(keyCode)];
	}

	Math::Vector2 InputController::GetMousePosition() const
	{
		return cursorPos;
	}

	Math::Vector2 InputController::GetMouseDeltaPosition() const
	{
		return cursorDeltaPos;
	}

	void InputController::ClearDelta()
	{
		cursorDeltaPos = Math::Vector2::GetZero();
	}
}