using System;
using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	public enum LightType
	{
		Sun,
		Point,
		Spotlight,
	}

	public sealed class Light : Component
	{
		#region Properties

		public Vector3 AmbientColor
		{
			get
			{
				Vector3 result;
				API_GetAmbientColor(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetAmbientColor(NativeHandle, ref value);
			}
		}

		public Vector3 DiffuseColor
		{
			get
			{
				Vector3 result;
				API_GetDiffuseColor(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetDiffuseColor(NativeHandle, ref value);
			}
		}

		public Vector3 SpecularColor
		{
			get
			{
				Vector3 result;
				API_GetSpecularColor(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetSpecularColor(NativeHandle, ref value);
			}
		}

		public LightType Type
		{
			get
			{
				int result;
				API_GetLightType(NativeHandle, out result);
				return (LightType)result;
			}
			set
			{
				API_SetLightType(NativeHandle, (int)value);
			}
		}

		public Vector2i TextureSize
		{
			get
			{
				Vector2i result;
				API_GetTextureSize(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetTextureSize(NativeHandle, ref value);
			}
		}

		public bool CastShadows
		{
			get
			{
				bool result;
				API_GetCastShadows(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetCastShadows(NativeHandle, value);
			}
		}

		public float Distance
		{
			get
			{
				float result;
				API_GetDistance(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetDistance(NativeHandle, value);
			}
		}

		public float Range
		{
			get
			{
				float result;
				API_GetRange(NativeHandle, out result);
				return result;
			}
			set
			{
				API_SetRange(NativeHandle, value);
			}
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetAmbientColor(IntPtr handle, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetAmbientColor(IntPtr handle, ref Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDiffuseColor(IntPtr handle, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetDiffuseColor(IntPtr handle, ref Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetSpecularColor(IntPtr handle, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetSpecularColor(IntPtr handle, ref Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetLightType(IntPtr handle, out int value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetLightType(IntPtr handle, int value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetTextureSize(IntPtr handle, out Vector2i value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetTextureSize(IntPtr handle, ref Vector2i value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetCastShadows(IntPtr handle, out bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetCastShadows(IntPtr handle, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDistance(IntPtr handle, out float value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetDistance(IntPtr handle, float value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetRange(IntPtr handle, out float value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetRange(IntPtr handle, float value);
		#endregion
	}
}
