using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	/// <summary>
	/// Provides methods used to control application.
	/// </summary>
	public static class Application
	{
		#region Properties

		/// <summary>
		/// Current screen size in pixels.
		/// </summary>
		public static Vector2i ScreenSize
		{
			get
			{
				Vector2i value;
				API_GetScreenSize(out value);
				return value;
			}
		}

		#endregion

		#region Methods

		/// <summary>
		/// Close window and end application execution.
		/// </summary>
		public static void Exit()
		{
			API_ApplicationExit();
		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_ApplicationExit();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetScreenSize(out Vector2i screenSize);

		#endregion
	}
}
