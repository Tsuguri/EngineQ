using System;

namespace EngineQ
{
	public abstract class Object
	{
		private IntPtr nativeHandle;
		protected internal IntPtr NativeHandle
		{
			get
			{
				if (nativeHandle == IntPtr.Zero)
					throw new Exception("Attempt to use destroyed object");

				return nativeHandle;
			}
		}

		// TMP
		protected Object()
		{
			Console.WriteLine($"Constructed {GetType()} with handle {nativeHandle}");
		}

		// TMP
		~Object()
		{
			Console.WriteLine($"Destructed {GetType()} with handle {nativeHandle}");
		}
	}
}
