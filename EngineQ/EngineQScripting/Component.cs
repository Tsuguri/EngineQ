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
				API_GetEntity(NativeHandle, out value);
				return value;
			}
		}

		public bool Enabled
		{
			get
			{
				throw new NotImplementedException();
			}

			set
			{
				throw new NotImplementedException();
			}
		}

		public bool EnabledInHierarchy
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntity(IntPtr handle, out Entity entity);

		#endregion
	}
}
