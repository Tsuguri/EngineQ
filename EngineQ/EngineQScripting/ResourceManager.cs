using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public class ResourceManager : EngineQ.Object
	{
		#region Properties

		public static ResourceManager Instance
		{
			get
			{
				ResourceManager instance;
				API_GetInstance(out instance);
				return instance;
			}
		}

		#endregion

		#region Methods

		public bool IsResourceRegistered<TResourceType>(string resourceId)
		{
			bool isRegistered;
			API_IsResourceRegistered(this.NativeHandle, typeof(TResourceType), resourceId, out isRegistered);
			return isRegistered;
		}

		public void RegisterResource<TResourceType>(string resourceId, string resourcePath)
			where TResourceType : Resource
		{
			API_RegisterResource(this.NativeHandle, typeof(TResourceType), resourceId, resourcePath);
		}

		public TResourceType GetResource<TResourceType>(string resourceId)
			where TResourceType : Resource
		{
			Resource resource;
			API_GetResource(this.NativeHandle, typeof(TResourceType), resourceId, out resource);
			return (TResourceType)resource;
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetInstance(out ResourceManager instance);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_IsResourceRegistered(IntPtr handle, Type resourceType, string resourceId, out bool isRegistered);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_RegisterResource(IntPtr handle, Type resourceType, string resourceId, string resourcePath);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetResource(IntPtr handle, Type resourceType, string resourceId, out Resource resourceHandle);

		#endregion
	}
}
