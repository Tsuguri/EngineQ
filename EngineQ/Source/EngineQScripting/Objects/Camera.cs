using System;
using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	public sealed class Camera : Component
	{
		#region Properties

		public bool UseCustomProjectionMatrix
		{
			get
			{
				bool value;
				API_GetUseCustomProjectionMatrix(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetUseCustomProjectionMatrix(this.NativeHandle, value);
			}
		}

		public Matrix4 ProjectionMatrix
		{
			get
			{
				Matrix4 value;
				API_GetProjectionMatrix(this.NativeHandle, out value);
				return value;
			}
		}

		public Matrix4 CustomProjectionMatrix
		{
			get
			{
				Matrix4 value;
				API_GetCustomProjectionMatrix(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetCustomProjectionMatrix(this.NativeHandle, ref value);
			}
		}

		public float FieldOfView
		{
			get
			{
				float value;
				API_GetFieldOfView(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetFieldOfView(this.NativeHandle, value);
			}
		}

		public float NearDistance
		{
			get
			{
				float value;
				API_GetNearDistance(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetNearDistance(this.NativeHandle, value);
			}
		}

		public float FarDistance
		{
			get
			{
				float value;
				API_GetFarDistance(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetFarDistance(this.NativeHandle, value);
			}
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetUseCustomProjectionMatrix(IntPtr handle, out bool value);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetUseCustomProjectionMatrix(IntPtr handle, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetProjectionMatrix(IntPtr handle, out Matrix4 value);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetCustomProjectionMatrix(IntPtr handle, out Matrix4 value);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetCustomProjectionMatrix(IntPtr handle, ref Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetFieldOfView(IntPtr handle, out float value);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetFieldOfView(IntPtr handle, float value);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetNearDistance(IntPtr handle, out float value);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetNearDistance(IntPtr handle, float value);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetFarDistance(IntPtr handle, out float value);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetFarDistance(IntPtr handle, float value);

		#endregion
	}
}
