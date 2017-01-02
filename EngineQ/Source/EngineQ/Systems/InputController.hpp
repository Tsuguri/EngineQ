#ifndef ENGINEQ_INPUTCONTROLLER_HPP
#define ENGINEQ_INPUTCONTROLLER_HPP

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"

// This project
#include "EngineQ/Scripting/ScriptEngine.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;
	}

	class InputController : private Utilities::Immovable
	{
		friend class Engine;

	private:
		class Initializer
		{
		public:
			Initializer();
		};

	public:
		enum class Key
		{
			Unknown = -1,

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
				
			Count,
		};

		enum class MouseButton
		{
			Unknown = -1,

			Left,
			Right,
			Middle,

			Button4,
			Button5,
			Button6,
			Button7,
			Button8,

			Count,
		};

		enum class KeyAction
		{
			Unknown = -1,

			Release,
			Press,
			Repeat
		};

	private:
		static Initializer initializer;

		bool keys[static_cast<int>(Key::Count)] = { false };
		bool mouseButtons[static_cast<int>(MouseButton::Count)] = { false };
		
		Scripting::ScriptEngine* se = nullptr;
		Scripting::ScriptMethod keyEventMethod = nullptr;
		Scripting::ScriptMethod mouseButtonEventMethod = nullptr;

		Math::Vector2 cursorPos;
		Math::Vector2 cursorDeltaPos;

		void OnKeyAction(int key, int scancode, int action, int mode);
		void OnMouseButtonAction(int button, int action, int mode);
		void OnMouseMoveAction(double xpos, double ypos);

		static void SetTranslateTables();

	public:
		void InitMethods(Scripting::ScriptEngine* se);
		bool IsButtonDown(Key keyCode);
		bool IsMouseButtonDown(MouseButton keyCode);

		Math::Vector2 GetMousePosition() const;
		Math::Vector2 GetMouseDeltaPosition() const;
		void ClearDelta();
	};
}

#endif