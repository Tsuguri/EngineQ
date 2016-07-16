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
			Space = 32,
			Apostrophe = 39,
			Comma = 44,
			Minus = 45,
			Period = 46,
			Slash = 47,
			N0 = 48,
			N1 = 49,
			N2 = 50,
			N3 = 51,
			N4 = 52,
			N5 = 53,
			N6 = 54,
			N7 = 55,
			N8 = 56,
			N9 = 57,
			Semicolon = 59,
			Equal = 61,
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			LeftBracket = 91,
			Backslash = 92,
			RightBracket = 93,
			GraveAccent = 96,
			World1 = 16,
			World2 = 16,
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,
			Kp0 = 320,
			Kp1 = 321,
			Kp2 = 322,
			Kp3 = 323,
			Kp4 = 324,
			Kp5 = 325,
			Kp6 = 326,
			Kp7 = 327,
			Kp8 = 328,
			Kp9 = 329,
			KpDecimal = 330,
			KpDivide = 331,
			KpMultiply = 332,
			KpSubtract = 333,
			KpAdd = 334,
			KpEnter = 335,
			KpEqual = 336,
			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348,
		}

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
