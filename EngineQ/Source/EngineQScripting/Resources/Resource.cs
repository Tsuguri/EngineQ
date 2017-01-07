using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Base class for all resources. Every Resoruce is managed by <see cref="ResourceManager"/>. 
	/// </summary>
	public abstract class Resource : EngineQ.Object
	{
		#region Properties

		/// <summary>
		/// Handle to resource memory.
		/// </summary>
		internal IntPtr Handle
		{
			get
			{
				return this.NativeHandle;
			}
		}

		#endregion

		#region Constructors and Destructors
		
		internal Resource()
		{
			API_IncRefCounter(this.NativeHandle);
		}

		~Resource()
		{
			API_DecRefCounter(this.NativeHandle);
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
