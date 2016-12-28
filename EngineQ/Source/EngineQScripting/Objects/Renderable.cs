using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public sealed class Renderable : Component
	{
		#region Properties
		
		public ShaderProperties ForwardShader
		{
			get
			{
				ShaderProperties value;
				API_GetForwardShader(this.NativeHandle, out value);
				return value;
			}
		}

		public ShaderProperties DeferredShader
		{
			get
			{
				ShaderProperties value;
				API_GetDeferredShader(this.NativeHandle, out value);
				return value;
			}
		}

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

		public bool CastShadows
		{
			get
			{
				bool value;
				API_GetCastShadows(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetCastShadows(this.NativeHandle, value);
			}
		}

		public bool Volumetric
		{
			get
			{
				bool value;
				API_GetVolumetric(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetVolumetric(this.NativeHandle, value);
			}
		}

		

		

		#endregion

		#region Methods

		public void UseForwardShader(Shader shader)
		{
			API_UseForwardShader(this.NativeHandle, shader.Handle);
		}
		
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

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetVolumetric(IntPtr nativeHandle, out bool volumetric);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetVolumetric(IntPtr nativeHandle, bool volumetric);

		#endregion
	}
}
