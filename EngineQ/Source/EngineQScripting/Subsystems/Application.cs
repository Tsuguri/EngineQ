using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Provides methods used to control application.
	/// </summary>
	public static class Application
	{
		/// <summary>
		/// Close window and end application execution.
		/// </summary>
		public static void Exit()
		{
			API_ApplicationExit();
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_ApplicationExit();

	}
}
