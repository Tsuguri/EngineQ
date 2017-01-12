using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Abstract representation of the scene object.
	/// Provides utilities for adding and removing <see cref="Component"/>s which provide functionality for Entities.
	/// </summary>
	public sealed class Entity : EngineQ.Object
	{
		/// <summary>
		/// Scene contaning this Entity.
		/// </summary>
		public Scene Scene
		{
			get
			{
				Scene value;
				API_GetScene(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// <see cref="Component"/> describing position, orientation and hierarchy of this Entity on the <see cref="EngineQ.Scene"/>. 
		/// </summary>
		public Transform Transform
		{
			get
			{
				Transform value;
				API_GetTransform(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Name of this Entity.
		/// Can be used to distinguish entities and search for them on the <see cref="EngineQ.Scene"/>.
		/// </summary>
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

		/// <summary>
		/// Specifies whether the Entity is enabled. 
		/// When set to false, the Entity will be disabled.
		/// Disabling Entity disables all children Entities and Components of this Entity. 
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
		/// Specifies whether the Entity is enabled in hierarchy.
		/// Entity can be disabled if it is disabled itself (<see cref="Enabled"/> is set to false), or it's parent <see cref="Transform.Parent"/> is disabled in hierarchy (<see cref="EnabledInHierarchy"/> is set to false).
		/// </summary>
		/// <seealso cref="Enabled"/>
		/// <seealso cref="EnabledInHierarchy"/>
		public bool EnabledInHierarchy
		{
			get
			{
				bool value;
				API_GetEnabledInHierarchy(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Gets first <see cref="Component"/> with specified or derrived type.
		/// </summary>
		/// <typeparam name="TComponent"><see cref="Component"/> direct or base type.</typeparam>
		/// <returns>Found <see cref="Component"/> or null when not found.</returns>
		public TComponent GetComponent<TComponent>()
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_GetComponentType(this.NativeHandle, ref type, out value);
			return (TComponent)value;
		}

		/// <summary>
		/// Creates and adds <see cref="Component"/> with given type to this Entity.
		/// </summary>
		/// <typeparam name="TComponent">Type of the <see cref="Component"/>.</typeparam>
		/// <param name="enabled">Specifies whether <see cref="Component"/> will be created as enabled or disabled.</param>
		/// <returns>Reference to created component.</returns>
		public TComponent AddComponent<TComponent>(bool enabled = true)
			where TComponent : Component
		{
			Component value;
			Type type = typeof(TComponent);
			API_AddComponent(this.NativeHandle, ref type, enabled, out value);
			return (TComponent)value;
		}

		/// <summary>
		/// Removes specified <see cref="Component"/> from this Entity and destroys it.
		/// </summary>
		/// <param name="component"><see cref="Component"/> to be removed and destroyed.</param>
		/// <exception cref="ArgumentException">Thrown when <paramref name="component"/> is not owned by this Entity  or it is <see cref="EngineQ.Transform"/> component.</exception>
		public void RemoveComponent(Component component)
		{
			API_RemoveComponent(this.NativeHandle, ref component);
		}

		/// <summary>
		/// Amount of <see cref="Component"/>s added to the Entity.
		/// </summary>
		public int ComponentsCount
		{
			get
			{
				int value;
				API_GetComponentsCount(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Gets <see cref="Component"/> with specified index.
		/// </summary>
		/// <param name="index">Index of the <see cref="Component"/>.</param>
		/// <returns><see cref="Component"/> at specified index.</returns>
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
		private static extern void API_AddComponent(IntPtr handle, ref Type type, bool enabled, out Component component);

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
