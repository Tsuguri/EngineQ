using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Provides performance information.
	/// </summary>
	public class Profiler
	{
		public static bool PrintInfo
		{
			get
			{
				bool value;
				API_GetPrintInfo(out value);
				return value;
			}

			set
			{
				API_SetPrintInfo(value);
			}
		}

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetPrintInfo(out bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetPrintInfo(bool value);

		#endregion
	}
}
