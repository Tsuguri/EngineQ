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
				float value;
				API_GetDeltaTime(out value);
				return value;
			}
		}

		/// <summary>
		/// Seconds since start of the application.
		/// </summary>
		public static float TimeFromStart
		{
			get
			{
				float value;
				API_GetTimeFromStart(out value);
				return value;
			}
		}


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDeltaTime(out float time);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetTimeFromStart(out float time);

		#endregion
	}
}
