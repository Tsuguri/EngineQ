using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// <see cref="Component"/> providing <see cref="EngineQ.Mesh"/> rendering capability - given mesh will appear on scene in <see cref="Entity"/> position.
	/// </summary>
	public sealed class Renderable : Component
	{
		#region Properties
		
		/// <summary>
		/// Properties of shader that will be used in case of forward rendering. Can be used to control it.
		/// </summary>
		public ShaderProperties ForwardShader
		{
			get
			{
				ShaderProperties value;
				API_GetForwardShader(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Properties of shader that will be used in case od deferred rendering. Can be used to control it.
		/// </summary>
		public ShaderProperties DeferredShader
		{
			get
			{
				ShaderProperties value;
				API_GetDeferredShader(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// <see cref="EngineQ.Mesh"/> that will be rendered by this <see cref="Renderable"/>
		/// </summary>
		public Mesh Mesh
		{
			get
			{
				Mesh mesh;
				API_GetMesh(this.NativeHandle, out mesh);
				return mesh;
			}

			set
			{
				API_SetMesh(this.NativeHandle, value.Handle);
			}
		}

		/// <summary>
		/// Indicates if rendered <see cref="EngineQ.Mesh"/> should cast shadows on other objects
		/// </summary>
		public bool CastShadows
		{
			get
			{
				bool castShadows;
				API_GetCastShadows(this.NativeHandle, out castShadows);
				return castShadows;
			}
			set
			{
				API_SetCastShadows(this.NativeHandle, value);
			}
		}

		#endregion

		#region Methods

		/// <summary>
		/// Sets usage of given <see cref="Shader"/> to render in case of forward rendering path.
		/// </summary>
		/// <param name="shader">Will be used to render given <see cref="EngineQ.Mesh"/></param>
		public void UseForwardShader(Shader shader)
		{
			API_UseForwardShader(this.NativeHandle, shader.Handle);
		}
		
		/// <summary>
		/// Sets usage of given <see cref="Shader"/> to render in case of deferred rendering path. It should be geometry pass shader.
		/// </summary>
		/// <param name="shader">Will be used in geometry pass to render given <see cref="EngineQ.Mesh"/></param>
		public void UseDeferredShader(Shader shader)
		{
			API_UseDeferredShader(this.NativeHandle, shader.Handle);
		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetForwardShader(IntPtr handle, out ShaderProperties forwardShader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDeferredShader(IntPtr handle, out ShaderProperties deferredShader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetMesh(IntPtr handle, out Mesh mesh);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetMesh(IntPtr handle, IntPtr meshHandle);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetCastShadows(IntPtr handle, out bool castShadowsValue);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetCastShadows(IntPtr handle, bool castShadowsValue);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_UseForwardShader(IntPtr handle, IntPtr shader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_UseDeferredShader(IntPtr handle, IntPtr shader);
		
		#endregion
	}
}
