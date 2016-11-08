using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public sealed class Entity : EngineQ.Object
	{
		public Scene Scene
		{
			get
			{
				Scene value;
				API_GetScene(this.NativeHandle, out value);
				return value;
			}
		}

		public Transform Transform
		{
			get
			{
				Transform value;
				API_GetTransform(this.NativeHandle, out value);
				return value;
			}
		}

		public string Name
		{
			get
			{
				string value;
				API_GetName(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetName(this.NativeHandle, value);
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

		public TComponent GetComponent<TComponent>()
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_GetComponentType(this.NativeHandle, ref type, out value);
			return (TComponent)value;
		}

		public TComponent AddComponent<TComponent>()
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_AddComponent(this.NativeHandle, ref type, out value);
			return (TComponent)value;
		}

		public void RemoveComponent(Component component)
		{
			API_RemoveComponent(this.NativeHandle, ref component);
		}

		public int ComponentsCount
		{
			get
			{
				int value;
				API_GetComponentsCount(this.NativeHandle, out value);
				return value;
			}
		}

		public Component GetComponent(int index)
		{
			Component value;
			API_GetComponentIndex(this.NativeHandle, index, out value);
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

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEnabled(IntPtr handle, out bool enabled);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetEnabled(IntPtr handle, bool enabled);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEnabledInHierarchy(IntPtr handle, out bool enabledInHierarchy);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetName(IntPtr handle, out string name);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetName(IntPtr handle, string name);

		#endregion
	}
}
