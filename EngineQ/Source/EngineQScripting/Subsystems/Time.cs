using System.Runtime.CompilerServices;

namespace EngineQ
{
	public static class Time
	{
		public static float DeltaTime
		{
			get
			{
				float value = 0.0f;
				API_GetDeltaTime(out value);
				return value;
			}
		}

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
