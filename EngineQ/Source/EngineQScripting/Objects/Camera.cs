using System;
using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	/// <summary>
	/// Component providing Camera functionality for <see cref="Entity"/>. 
	/// </summary>
	public sealed class Camera : Component
	{
		#region Properties

		/// <summary>
		/// Specifies whether to use custom projection matrix.
		/// </summary>
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

		/// <summary>
		/// Current projection matrix.
		/// </summary>
		public Matrix4 ProjectionMatrix
		{
			get
			{
				Matrix4 value;
				API_GetProjectionMatrix(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Custom projection matrix. It will be used only when <see cref="UseCustomProjectionMatrix"/> is set to true.
		/// </summary>
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

		/// <summary>
		/// Field of view in degrees.
		/// </summary>
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

		/// <summary>
		/// Near clipping plane distance.
		/// </summary>
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

		/// <summary>
		/// Far clipping plane distance.
		/// </summary>
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

		#region Methods

		/// <summary>
		/// Get world space ray from screen position. 
		/// </summary>
		/// <param name="position">Position on screen. Ranges from -1 to 1 on both coordinates.</param>
		/// <returns>World space ray from camera screen position.</returns>
		public Ray GetViewRay(Vector2 position)
		{
			var inverseView = this.Entity.Transform.GlobalMatrix;
			var inverseProjection = this.ProjectionMatrix.Inverse;

			Vector4 direction = new Vector4(position, 1.0f, 1.0f);

			direction = inverseView * inverseProjection * direction;

			direction.X /= direction.W;
			direction.Y /= direction.W;
			direction.Z /= direction.W;

			Vector3 origin = this.Entity.Transform.GlobalPosition;

			return new Ray(origin, ((Vector3)direction - origin).Normalized);
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
