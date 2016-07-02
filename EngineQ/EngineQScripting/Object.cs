using System;

namespace EngineQ
{
	public abstract class Object
	{
		protected readonly IntPtr nativeHandle;

		public Object()
		{
			// TMP
			Console.WriteLine($"Constructed {GetType()} with handle {nativeHandle}");
		}

		~Object()
		{
			// TMP
			Console.WriteLine($"Destructed {GetType()} with handle {nativeHandle}");
		}
	}
}
