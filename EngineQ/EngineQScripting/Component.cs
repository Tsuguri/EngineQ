using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public abstract class Component : EngineQ.Object
	{
		#region Properties

		public Entity Entity
		{
			get
			{
				Entity value;
				API_GetEntity(this.NativeHandle, out value);
				return value;
			}
		}

		public bool Enabled
		{
			get
			{
				bool value;
				API_GetEnabled(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetEnabled(this.NativeHandle, value);
			}
		}

		public bool EnabledInHierarchy
		{
			get
			{
				bool value;
				API_GetEnabledInHierarchy(this.NativeHandle, out value);
				return value;
			}
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntity(IntPtr handle, out Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEnabled(IntPtr handle, out bool isEnabled);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetEnabled(IntPtr handle, bool isEnabled);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEnabledInHierarchy(IntPtr handle, out bool isEnabledInHierarchy);
		
		#endregion
	}
}
