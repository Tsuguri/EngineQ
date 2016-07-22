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

		public enum MouseButton
		{
			Left = 0,
			Right = 1,
			Middle = 2
		}

		public enum KeyAction
		{
			Release = 0,
			Press = 1,
			Repeat = 2
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
		private static bool tmpBool;
		private static Vector2 tmpVector2;
		private static KeyEventHandler tmpKeh;

		private static Dictionary<Key, KeyEventHandler> keyEventDict;
		private static Dictionary<MouseButton, KeyEventHandler> mouseEventDict;

		#endregion

		#region Properties

		public static Vector2 MousePosition
		{
			get
			{
				API_MousePosition(out tmpVector2);
				return tmpVector2;
			}
		}

		public static Vector2 MouseDeltaPosition
		{
			get
			{
				API_MouseDeltaPosition(out tmpVector2);
				return tmpVector2;
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
			API_KeyPressed((int)key, out tmpBool);
			return tmpBool;
		}

		// ReSharper disable once UnusedMember.Local
		private static void KeyEvent(Key key, KeyAction action)
		{
			if (keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh.OnEvent(action);
			}
		}

		public static void ListenKey(Key key, EventType action)
		{
			if (!keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh = new KeyEventHandler();
				keyEventDict.Add(key, tmpKeh);
			}
			tmpKeh.Event += action;
		}

		public static void StopListening(Key key, EventType action)
		{
			if (keyEventDict.TryGetValue(key, out tmpKeh))
			{
				tmpKeh.Event -= action;
			}
		}

		#endregion

		#region Mouse

		public static bool MouseButtonDown(int button)
		{
			API_MouseButtonDown(button, out tmpBool);
			return tmpBool;
		}

		// ReSharper disable once UnusedMember.Local
		private static void MouseButtonEvent(MouseButton button, KeyAction action)
		{
			if (mouseEventDict.TryGetValue(button, out tmpKeh))
			{
				tmpKeh.OnEvent(action);
			}
		}

		public static void ListenMouseButton(MouseButton button, EventType action)
		{
			if (!mouseEventDict.TryGetValue(button, out tmpKeh))
			{
				tmpKeh = new KeyEventHandler();
				mouseEventDict.Add(button, tmpKeh);
			}
			tmpKeh.Event += action;
		}

		public static void StopListeningMouseButton(MouseButton button, EventType action)
		{
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
