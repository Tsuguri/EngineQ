using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Provides utilities to measuring time.
	/// </summary>
	public static class Time
	{
		/// <summary>
		/// Seconds since last update.
		/// </summary>
		public static float DeltaTime
		{
			get
			{
				float value = 0.0f;
				API_GetDeltaTime(out value);
				return value;
			}
		}

		/// </summary>
		/// Milliseconds since start of the application.
		/// <summary>
		public static ulong GetMillisecondsFromStart
		{
			get
			{
				ulong value = 0;
				API_GetMillisecondsFromStart(out value);
				return value;
			}
		}


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDeltaTime(out float time);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetMillisecondsFromStart(out ulong time);

		#endregion
	}
}
