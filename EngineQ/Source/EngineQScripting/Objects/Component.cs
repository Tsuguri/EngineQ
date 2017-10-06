using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Base class for all components that can be added to the <see cref="EngineQ.Entity"/>.
	/// </summary>
	/// <seealso cref="Transform"/>
	/// <seealso cref="Camera"/>
	/// <seealso cref="Light"/>
	/// <seealso cref="Renderable"/>
	/// <seealso cref="Script"/>
	public abstract class Component : EngineQ.Object
	{
		#region Properties

		/// <summary>
		/// Entity owning this Component.
		/// </summary>
		public Entity Entity
		{
			get
			{
				Entity value;
				API_GetEntity(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Specifies whether the Component is enabled. 
		/// When set to false, the Component will be disabled.
		/// Disabled components have no effect on its' parent <see cref="EngineQ.Entity"/>.
		/// </summary>
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

		/// <summary>
		/// Specifies whether the Component is enabled in hierarchy.
		/// Component can be disabled if it is disabled itself (<see cref="Enabled"/> is set to false), or it's parent <see cref="EngineQ.Entity"/> is disabled in hierarchy (<see cref="EngineQ.Entity.EnabledInHierarchy"/> is set to false).
		/// Disabled Components have no effect on its' parent <see cref="EngineQ.Entity"/>.
		/// </summary>
		/// <seealso cref="Entity.Enabled"/>
		/// <seealso cref="Entity.EnabledInHierarchy"/>
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
