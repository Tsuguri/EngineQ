using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	/// <summary>
	/// Provides information about user input such as keyboard keys presses, mouse cursor position and mouse button presses.
	/// </summary>
	public static class Input
	{
		#region Types

		/// <summary>
		/// Specifies all possible keyboard keys.
		/// </summary>
		public enum Key
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

		/// <summary>
		/// Specifies all possible mouse buttons.
		/// </summary>
		public enum MouseButton
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
		}

		/// <summary>
		/// Specifies all possible keyboard key and mouse button action types.
		/// </summary>
		public enum KeyAction
		{
			Unknown = -1,

			Release,
			Press,
			Repeat
		}

		/// <summary>
		/// Delegate used to register keyboard key events.
		/// </summary>
		/// <param name="key">Which keyboard key caused event.</param>
		/// <param name="action">Which action caused event.</param>
		public delegate void KeyboardKeyEventHandler(Key key, KeyAction action);
		/// <summary>
		/// Delegate used to register mouse button events.
		/// </summary>
		/// <param name="button">Which mouse button caused event.</param>
		/// <param name="action">Which action caused event.</param>
		public delegate void MouseButtonEventHandler(MouseButton button, KeyAction action);

		#endregion

		#region Static Fields

		private static KeyboardKeyEventHandler[] keyboardEvents;
		private static MouseButtonEventHandler[] mouseEvents;

		#endregion

		#region Static Properties

		/// <summary>
		/// Mouse position on the screen. Counted in pixels from the upper left corner of the screen.
		/// </summary>
		public static Vector2 MousePosition
		{
			get
			{
				Vector2 value;
				API_MousePosition(out value);
				return value;
			}
		}

		/// <summary>
		/// Amount of pixels by which the mouse position has changed since last update.
		/// </summary>
		public static Vector2 MouseDeltaPosition
		{
			get
			{
				Vector2 value;
				API_MouseDeltaPosition(out value);
				return value;
			}
		}

		#endregion

		#region Static Constructor

		static Input()
		{
			keyboardEvents = new KeyboardKeyEventHandler[(int)Key.Count];
			mouseEvents = new MouseButtonEventHandler[(int)MouseButton.Count];
		}

		#region Keys

		private static void KeyEvent(Key key, KeyAction action)
		{
			if (key == Key.Unknown)
				return;

			var keyboardEventHandler = keyboardEvents[(int)key];
			keyboardEventHandler?.Invoke(key, action);
		}

		/// <summary>
		/// Checks if specified keyboard key is pressed.
		/// </summary>
		/// <param name="key">Keyboard key which is checked.</param>
		/// <returns>True if the key is currently pressed.</returns>
		public static bool IsKeyPressed(Key key)
		{
			bool value;
			API_KeyPressed((int)key, out value);
			return value;
		}
		
		/// <summary>
		/// Registers action to be executed when state of the specified keyboard key has changed.
		/// </summary>
		/// <param name="key">Keyboard key which change will trigger action.</param>
		/// <param name="action">Action to be executed.</param>
		public static void RegisterKeyEvent(Key key, KeyboardKeyEventHandler action)
		{
			keyboardEvents[(int)key] += action;
		}

		/// <summary>
		/// Deregisters action executed when state of the specified keyboard key has changed.
		/// </summary>
		/// <param name="key">Keyboard key which change would trigger action.</param>
		/// <param name="action">Action to be removed.</param>
		public static void DeregisterKeyEvent(Key key, KeyboardKeyEventHandler action)
		{
			keyboardEvents[(int)key] -= action;
		}

		#endregion

		#region Mouse
		
		private static void MouseButtonEvent(MouseButton button, KeyAction action)
		{
			if (button == MouseButton.Unknown)
				return;

			var mouseEventHandler = mouseEvents[(int)button];
			mouseEventHandler?.Invoke(button, action);
		}

		/// <summary>
		/// Checks if specified mouse button is pressed.
		/// </summary>
		/// <param name="button">Mouse button which is checked.</param>
		/// <returns>True if the button is currently pressed.</returns>
		public static bool IsMouseButtonPressed(MouseButton button)
		{
			bool value;
			API_MouseButtonDown((int)button, out value);
			return value;
		}

		/// <summary>
		/// Registers action to be executed when state of the specified mouse button has changed.
		/// </summary>
		/// <param name="button">Mouse button which change will trigger action.</param>
		/// <param name="action">Action to be executed.</param>
		public static void RegisterMouseButtonEvent(MouseButton button, MouseButtonEventHandler action)
		{
			mouseEvents[(int)button] += action;
		}

		/// <summary>
		/// Deregisters action executed when state of the specified mouse button has changed.
		/// </summary>
		/// <param name="button">Mouse button which change would trigger action.</param>
		/// <param name="action">Action to be removed.</param>
		public static void DeregisterMouseButtonEvent(MouseButton button, MouseButtonEventHandler action)
		{
			mouseEvents[(int)button] -= action;
		}

		#endregion

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_KeyPressed(int key, out bool result);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MouseButtonDown(int button, out bool result);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MousePosition(out Vector2 result);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MouseDeltaPosition(out Vector2 result);

		#endregion
	}
}
