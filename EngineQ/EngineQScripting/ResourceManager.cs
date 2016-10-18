using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public class ResourceManager : EngineQ.Object
	{
		#region Types

		private delegate Resource ResourceContructor(IntPtr handle);
		
		#endregion

		#region Static Fields
		
		private static readonly Dictionary<Type, ResourceContructor> Constructors = new Dictionary<Type, ResourceContructor>
		{
			{ typeof(Shader), (handle) => new Shader(handle) },
			{ typeof(Texture), (handle) => new Texture(handle) },
		};

		#endregion

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

			ResourceContructor constructor;
			if(!Constructors.TryGetValue(resourceType, out constructor))
				throw new NotSupportedException($"Resource type {resourceType} is not supported");

			IntPtr resourceHandle;
			API_GetResource(this.NativeHandle, resourceType, resourceId, out resourceHandle);
			
			return (TResourceType)constructor(resourceHandle);
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetInstance(out ResourceManager instance);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetResource(IntPtr handle, Type resourceType, string resourceId, out IntPtr resourceHandle);

		#endregion
	}
}
