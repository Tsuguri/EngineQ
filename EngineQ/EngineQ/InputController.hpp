#ifndef ENGINEQ_INPUTCONTROLLER_HPP
#define ENGINEQ_INPUTCONTROLLER_HPP
#include "Math/Vector2.hpp"
#include "Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;
	}
	class InputController : public Utilities::Immovable
	{
	public:
		enum Key
		{
			Space,
			Apostrophe,
			Comma,
			Minus,
			Period,
			Slash,
			N0,
			N1,
			N2,
			N3,
			N4,
			N5,
			N6,
			N7,
			N8,
			N9,
			Semicolon,
			Equal,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			LeftBracket,
			Backslash,
			RightBracket,
			GraveAccent,
			World1,
			World2,
			Escape,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,
			Right,
			Left,
			Down,
			Up,
			PageUp,
			PageDown,
			Home,
			End,
			CapsLock,
			ScrollLock,
			NumLock,
			PrintScreen,
			Pause,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,
			Kp0,
			Kp1,
			Kp2,
			Kp3,
			Kp4,
			Kp5,
			Kp6,
			Kp7,
			Kp8,
			Kp9,
			KpDecimal,
			KpDivide,
			KpMultiply,
			KpSubtract,
			KpAdd,
			KpEnter,
			KpEqual,
			LeftShift,
			LeftControl,
			LeftAlt,
			LeftSuper,
			RightShift,
			RightControl,
			RightAlt,
			RightSuper,
			Menu,
		};
		
	private:

		friend class Engine;

		int translateTable[512];
		bool keys[128];
		bool mouseButtons[10];
		Scripting::ScriptEngine* se=nullptr;
		Scripting::ScriptMethod keyEventMethod=nullptr;
		Scripting::ScriptMethod mouseButtonEventMethod=nullptr;

		Math::Vector2 cursorPos;
		Math::Vector2 cursorDeltaPos;

		void KeyAction(int key, int scancode, int action, int mode);
		void MouseButtonAction(int button, int action, int mode);
		void MouseMoveAction(double xpos, double ypos);

		void SetTranslateTable();
	public:
		InputController();
		void InitMethods(Scripting::ScriptEngine* se);
		bool isButtonDown(Key keyCode);
		bool isMouseButtonDown(int keyCode);
		Math::Vector2 GetMousePosition() const;
		Math::Vector2 GetMouseDeltaPosition() const;
		void ClearDelta();
	};
}

#endif