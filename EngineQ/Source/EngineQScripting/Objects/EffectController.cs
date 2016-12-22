using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	public class EffectController : Object
	{
		#region Properties

		protected ShaderProperties Shader
		{
			get
			{
				ShaderProperties value;
				API_GetShaderProperties(this.NativeHandle, out value);
				return value;
			}
		}

		protected Scene Scene
		{
			get
			{
				Scene value;
				API_GetScene(this.NativeHandle, out value);
				return value;
			}
		}

		#endregion

		#region Methods

		protected virtual void OnCreate()
		{
		}

		protected virtual void OnUpdate()
		{
		}

		protected virtual void OnBeforeRender()
		{
		}

		protected virtual void OnAfterRender()
		{
		}

		protected virtual void OnDestroy()
		{
		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetShaderProperties(IntPtr handle, out ShaderProperties shaderProperties);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetScene(IntPtr handle, out Scene scene);
		
		#endregion
	}
}
