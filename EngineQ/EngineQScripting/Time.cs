using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ
{
	static class Time
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
