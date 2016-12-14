using System.Runtime.CompilerServices;

namespace EngineQ
{
	public static class Time
	{
		public static float DeltaTime
		{
			get
			{
				float time = 0;
				API_GetDeltaTime(out time);
				return time;
			}
		}

		public static float TimeFromStart
		{
			get
			{
				float time = 0;
				API_GetTimeFromStart(out time);
				return time;
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
