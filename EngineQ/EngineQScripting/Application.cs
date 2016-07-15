using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

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
