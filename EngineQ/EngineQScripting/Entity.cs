using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public sealed class Entity : Object
	{
		public Scene Scene
		{
			get
			{
				Scene value;
				API_GetScene(nativeHandle, out value);
				return value;
			}
		}

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

		public TComponent AddComponent<TComponent>()
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_AddComponent(nativeHandle, ref type, out value);
			return (TComponent)value;
		}

		public void RemoveComponent(Component component)
		{
			API_RemoveComponent(nativeHandle, ref component);
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
		private static extern void API_GetScene(IntPtr handle, out Scene scene);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetTransform(IntPtr handle, out Transform transform);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentIndex(IntPtr handle, int index, out Component component);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentsCount(IntPtr handle, out int count);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetComponentType(IntPtr handle, ref Type type, out Component component);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_AddComponent(IntPtr handle, ref Type type, out Component component);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_RemoveComponent(IntPtr handle, ref Component component);

		#endregion
	}
}
