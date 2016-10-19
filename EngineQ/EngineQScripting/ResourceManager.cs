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

		public TResourceType GetResource<TResourceType>(string resourceId)
			where TResourceType : Resource
		{
			Type resourceType = typeof(TResourceType);
			
			Resource resource;
			API_GetResource(this.NativeHandle, resourceType, resourceId, out resource);
			
			return (TResourceType)resource;
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetInstance(out ResourceManager instance);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetResource(IntPtr handle, Type resourceType, string resourceId, out Resource resourceHandle);

		#endregion
	}
}
