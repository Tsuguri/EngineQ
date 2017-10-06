using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Container object prepresenting rendered scene. 
	/// </summary>
	public sealed class Scene : EngineQ.Object
	{
		/// <summary>
		/// Finds <see cref="Entity"/> with given name. In case of multiple founds, first is returned.
		/// </summary>
		/// <param name="name">Name of <see cref="Entity"/> to find</param>
		/// <returns></returns>
		public Entity FindEntity(string name)
		{
			Entity entity;
			API_FindEntity(this.NativeHandle, name, out entity);
			return entity;
		}

		/// <summary>
		/// Creates new <see cref="Entity"/> with given <paramref name="name"/>.
		/// </summary>
		/// <param name="enabled">true if Entity should be activated immediately.</param>
		/// <param name="name">Name of created entity.</param>
		/// <returns></returns>
		public Entity CreateEntity(bool enabled = true, string name = "")
		{
			Entity value;
			API_CreateEntity(NativeHandle, enabled, name, out value);
			return value;
		}
		
		/// <summary>
		/// Removes <see cref="Entity"/> with given 0-based index.
		/// </summary>
		/// <param name="index">0-based index of <see cref="Entity"/> to remove.</param>
		public void RemoveEntity(int index)
		{
			API_RemoveEntityIndex(NativeHandle, index);
		}

		/// <summary>
		/// Removes given <see cref="Entity"/> from scene.
		/// </summary>
		/// <param name="entity"><see cref="Entity"/> to be removed from scene</param>
		public void RemoveEntity(Entity entity)
		{
			API_RemoveEntityRef(NativeHandle, ref entity);
		}

		/// <summary>
		/// Returns scene index of given <see cref="Entity"/>.
		/// </summary>
		/// <param name="entity"><see cref="Entity"/> belonging to scene which index should be returned</param>
		/// <returns>Index of given <see cref="Entity"/></returns>
		public int GetEntityIndex(Entity entity)
		{
			int value;
			API_GetEntityIndex(NativeHandle, ref entity, out value);
			return value;
		}

		/// <summary>
		/// Finds <see cref="Entity"/> with given index.
		/// </summary>
		/// <param name="index">Index of <see cref="Entity"/></param>
		/// <returns><see cref="Entity"/> placed under given index</returns>
		public Entity GetEntity(int index)
		{
			Entity value;
			API_GetEntity(NativeHandle, index, out value);
			return value;
		}
		/// <summary>
		/// Number of <see cref="Entity"/> in <see cref="Scene"/>. 
		/// </summary>
		public int EntitiesCount
		{
			get
			{
				int value;
				API_GetEntitiesCount(NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Currently active <see cref="Camera"/>
		/// </summary>
		public Camera ActiveCamera
		{
			get
			{
				Camera value;
				API_GetActiveCamera(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetActiveCamera(this.NativeHandle, value);
			}
		}

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_FindEntity(IntPtr handle, string name, out Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateEntity(IntPtr handle, bool enabled, string name, out Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_RemoveEntityIndex(IntPtr handle, int index);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_RemoveEntityRef(IntPtr handle, ref Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntityIndex(IntPtr handle, ref Entity entity, out int index);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntity(IntPtr handle, int index, out Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEntitiesCount(IntPtr handle, out int count);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetActiveCamera(IntPtr handle, out Camera camera);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetActiveCamera(IntPtr handle, Camera camera);

		#endregion
	}
}
