using System.Runtime.CompilerServices;

namespace EngineQ
{
	public static class Application
	{
		public static void Exit()
		{
			API_ApplicationExit();
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_ApplicationExit();

	}
}
