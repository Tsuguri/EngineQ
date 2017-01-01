using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Manages resources (objects derrived from <see cref="Resource"/> class) such as <see cref="Texture"/>s, <see cref="Shader"/>s, <see cref="Model"/>s and <see cref="Mesh"/>es. 
	/// Provides utilties for resource loading. Manages resource liftetime and unloads unused resources.
	/// </summary>
	public sealed class ResourceManager : EngineQ.Object
	{
		#region Properties

		/// <summary>
		/// Instance of current Resource Manager.
		/// </summary>
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

		/// <summary>
		/// Checks if resource of specified type and id is already registered.
		/// </summary>
		/// <typeparam name="TResourceType">Type of the resource.</typeparam>
		/// <param name="resourceId">Id of the resource.</param>
		/// <returns>True if resource is already registered.</returns>
		public bool IsResourceRegistered<TResourceType>(string resourceId)
		{
			bool isRegistered;
			API_IsResourceRegistered(this.NativeHandle, typeof(TResourceType), resourceId, out isRegistered);
			return isRegistered;
		}
		
		/// <summary>
		/// Registers resource of given type with specified unique resource id and path to resource file.
		/// </summary>
		/// <typeparam name="TResourceType">Type of the resource.</typeparam>
		/// <param name="resourceId">Id of the resource.</param>
		/// <param name="resourcePath">Path to the resouce file on disk.</param>
		public void RegisterResource<TResourceType>(string resourceId, string resourcePath)
			where TResourceType : Resource
		{
			API_RegisterResource(this.NativeHandle, typeof(TResourceType), resourceId, resourcePath);
		}

		/// <summary>
		/// Get resource of given type with specified id. 
		/// If resource is not already loaded, then it will be created using registered path to resource file. Otherwise the reference to the existing resource will be returned.
		/// </summary>
		/// <typeparam name="TResourceType">Type of the resource.</typeparam>
		/// <param name="resourceId">Id of the resource.</param>
		/// <returns>Reference to the resource object.</returns>
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
