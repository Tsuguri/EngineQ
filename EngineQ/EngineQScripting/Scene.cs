using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public class Scene : Object
	{
		public Entity CreateEntity()
		{
			Entity value;
			API_CreateEntity(nativeHandle, out value);
			return value;
		}

		public void RemoveEntity(int index)
		{
			API_RemoveEntityIndex(nativeHandle, index);
		}

		public void RemoveEntity(Entity entity)
		{
			API_RemoveEntityRef(nativeHandle, ref entity);
		}

		public int GetEntityIndex(Entity entity)
		{
			int value;
			API_GetEntityIndex(nativeHandle, ref entity, out value);
			return value;
		}

		public Entity GetEntity(int index)
		{
			Entity value;
			API_GetEntity(nativeHandle, index, out value);
			return value;
		}

		public int EntitiesCount
		{
			get
			{
				int value;
				API_GetEntitiesCount(nativeHandle, out value);
				return value;
			}
		}

		#region API

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
