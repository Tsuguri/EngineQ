using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public sealed class Entity : Object
	{
		public Transform Transform
		{
			get
			{
				Transform value;
				API_GetTransform(nativeHandle, out value);
				return value;
			}
		}
		
		public TComponent GetComponent<TComponent>()
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_GetComponentType(nativeHandle, ref type, out value);
			return (TComponent)value;
		}

		public TScript AddScript<TScript>()
			where TScript : Script
		{
			Script value;
			Type type = typeof(TScript);
			API_AddScript(nativeHandle, ref type, out value);
			return (TScript)value;
		}

		public int ComponentsCount
		{
			get
			{
				int value;
				API_GetComponentsCount(nativeHandle, out value);
				return value;
			}
		}

		public Component GetComponent(int index)
		{
			Component value;
			API_GetComponentIndex(nativeHandle, index, out value);
			return value;
		}

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetTransform(IntPtr handle, out Transform transform);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentIndex(IntPtr handle, int index, out Component component);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentsCount(IntPtr handle, out int count);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentType(IntPtr handle, ref Type type, out Component component);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_AddScript(IntPtr handle, ref Type type, out Script script);

		#endregion
	}
}
