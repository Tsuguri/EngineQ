using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public abstract class Resource
	{
		#region Fields

		public readonly IntPtr Handle;

		#endregion

		#region Constructors and Destructors

		protected Resource(IntPtr handle)
		{
			this.Handle = handle;

			API_IncRefCounter(this.Handle);
		}

		~Resource()
		{
			API_DecRefCounter(this.Handle);
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_IncRefCounter(IntPtr handle);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_DecRefCounter(IntPtr handle);

		#endregion
	}
}
