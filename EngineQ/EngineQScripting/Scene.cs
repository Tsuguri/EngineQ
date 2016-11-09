using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public sealed class Scene : EngineQ.Object
	{
		public Entity FindEntity(string name)
		{
			Entity entity;
			API_FindEntity(this.NativeHandle, name, out entity);
			return entity;
		}

		public Entity CreateEntity()
		{
			Entity value;
			API_CreateEntity(NativeHandle, out value);
			return value;
		}

		public void RemoveEntity(int index)
		{
			API_RemoveEntityIndex(NativeHandle, index);
		}

		public void RemoveEntity(Entity entity)
		{
			API_RemoveEntityRef(NativeHandle, ref entity);
		}

		public int GetEntityIndex(Entity entity)
		{
			int value;
			API_GetEntityIndex(NativeHandle, ref entity, out value);
			return value;
		}

		public Entity GetEntity(int index)
		{
			Entity value;
			API_GetEntity(NativeHandle, index, out value);
			return value;
		}

		public int EntitiesCount
		{
			get
			{
				int value;
				API_GetEntitiesCount(NativeHandle, out value);
				return value;
			}
		}

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_FindEntity(IntPtr handle, string name, out Entity entity);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateEntity(IntPtr handle, out Entity entity);

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

		#endregion
	}
}
