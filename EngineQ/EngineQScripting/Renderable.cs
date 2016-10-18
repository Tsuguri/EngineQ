using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public class Renderable : Component
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

		#endregion

		#region Methods

		public void SetForwardShader(Shader shader)
		{
			API_SetForwardShader(this.NativeHandle, shader.Handle);
		}

		public void SetDeferredShader(Shader shader)
		{
			API_SetDeferredShader(this.NativeHandle, shader.Handle);
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetForwardShader(IntPtr handle, out ShaderProperties forwardShader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDeferredShader(IntPtr handle, out ShaderProperties deferredShader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetForwardShader(IntPtr handle, IntPtr shader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetDeferredShader(IntPtr handle, IntPtr shader);
		
		#endregion
	}
}
