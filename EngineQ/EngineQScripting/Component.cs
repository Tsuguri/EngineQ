using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public abstract class Component : Object
	{
		#region Properties

		public Entity Entity
		{
			get
			{
				Entity value;
				API_GetEntity(nativeHandle, out value);
				return value;
			}
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntity(IntPtr handle, out Entity entity);

		#endregion
	}
}
