using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using EngineQ.Math;

namespace EngineQ
{

	public static class Input
	{
		#region Types

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

		public enum KeyAction
		{
			Unknown = -1,

			Release,
			Press,
			Repeat
		}

		public delegate void EventType(KeyAction action);

		private sealed class KeyEventHandler
		{

			public event EventType Event;

			public void OnEvent(KeyAction action)
			{
				Event?.Invoke(action);
			}
		}

		#endregion

		#region Fields

		private static Dictionary<Key, KeyEventHandler> keyEventDict;
		private static Dictionary<MouseButton, KeyEventHandler> mouseEventDict;

		#endregion

		#region Properties

		public static Vector2 MousePosition
		{
			get
			{
				Vector2 value;
				API_MousePosition(out value);
				return value;
			}
		}

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

		#region Methods

		static Input()
		{
			keyEventDict = new Dictionary<Key, KeyEventHandler>();
			mouseEventDict = new Dictionary<MouseButton, KeyEventHandler>();
		}

		#region Keys

		public static bool KeyPressed(Key key)
		{
			bool value;
			API_KeyPressed((int)key, out value);
			return value;
		}

		// ReSharper disable once UnusedMember.Local
		private static void KeyEvent(Key key, KeyAction action)
		{
			KeyEventHandler tmpKeh;
			if (keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh.OnEvent(action);
			}
		}

		public static void ListenKey(Key key, EventType action)
		{
			KeyEventHandler tmpKeh;
			if (!keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh = new KeyEventHandler();
				keyEventDict.Add(key, tmpKeh);
			}
			tmpKeh.Event += action;
		}

		public static void StopListeningKey(Key key, EventType action)
		{
			KeyEventHandler tmpKeh;
			if (keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh.Event -= action;
			}
		}

		#endregion

		#region Mouse

		public static bool MouseButtonDown(MouseButton button)
		{
			bool value;
			API_MouseButtonDown((int)button, out value);
			return value;
		}

		// ReSharper disable once UnusedMember.Local
		private static void MouseButtonEvent(MouseButton button, KeyAction action)
		{
			KeyEventHandler tmpKeh;
			if (mouseEventDict.TryGetValue(button, out tmpKeh))
			{
				tmpKeh.OnEvent(action);
			}
		}

		public static void ListenMouseButton(MouseButton button, EventType action)
		{
			KeyEventHandler tmpKeh;
			if (!mouseEventDict.TryGetValue(button, out tmpKeh))
			{
				tmpKeh = new KeyEventHandler();
				mouseEventDict.Add(button, tmpKeh);
			}
			tmpKeh.Event += action;
		}

		public static void StopListeningMouseButton(MouseButton button, EventType action)
		{
			KeyEventHandler tmpKeh;
			if (mouseEventDict.TryGetValue(button, out tmpKeh))
			{
				tmpKeh.Event -= action;
			}
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
