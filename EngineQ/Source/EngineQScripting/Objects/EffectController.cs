using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Base class for all user-defined controllers of postprocessing effects.
	/// </summary>
	public class EffectController : Object
	{
		#region Properties

		/// <summary>
		/// Postprocessing effect shader.
		/// </summary>
		protected ShaderProperties Shader
		{
			get
			{
				ShaderProperties value;
				API_GetShaderProperties(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Current scene.
		/// </summary>
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

		/// <summary>
		/// When overriden, invoked once, on effect creation.
		/// </summary>
		protected virtual void OnCreate()
		{
		}

		/// <summary>
		/// When overriden, invoked once every scene update.
		/// </summary>
		protected virtual void OnUpdate()
		{
		}

		/// <summary>
		/// When overriden, invoked once before postprocessing effect is applied. 
		/// </summary>
		protected virtual void OnBeforeRender()
		{
		}

		/// <summary>
		/// When overriden, invoked once after postprocessing effect is applied. 
		/// </summary>
		protected virtual void OnAfterRender()
		{
		}

		/// <summary>
		/// When overriden, invoked once when effect is removed.
		/// </summary>
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
