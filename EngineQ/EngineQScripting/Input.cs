﻿using System.Runtime.CompilerServices;

namespace EngineQ
{

	public static class Input
	{
		public enum Key
		{
			Space = 32,
			Apostrophe = 3,
			Comma = 4,
			Minus = 4,
			Period = 4,
			Slash = 4,
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
			Semicolon = 5,
			Equal = 6,
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
			LeftBracket = 9,
			Backslash = 9,
			RightBracket = 9,
			GraveAccent = 9,
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
			Left,
			Right,
		}

		private static bool tmp;

		public static bool KeyPressed(Key key)
		{
			API_KeyPressed((int)key, out tmp);
			return tmp;
		}

		public static bool MouseButtonDown(MouseButton button)
		{
			API_MouseButtonDown((int)button, out tmp);
			return tmp;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_KeyPressed(int key, out bool result);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MouseButtonDown(int button, out bool result);

	}
}
