using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	using Math;

	public sealed class Transform : Component
	{
		#region Properties

		public Transform Parent
		{
			get
			{
				Transform value;
				API_GetParent(NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetParent(NativeHandle, ref value);
			}
		}

		public Vector3 Position
		{
			get
			{
				Vector3 value;
				API_GetPosition(NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetPosition(NativeHandle, ref value);
			}
		}

		public Vector3 GlobalPosition
		{
			get
			{
				throw new NotImplementedException();
			}
			set
			{
				throw new NotImplementedException();
			}
		}

		public Vector3 Scale
		{
			get
			{
				Vector3 value;
				API_GetScale(NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetScale(NativeHandle, ref value);
			}
		}

		public Vector3 GlobalScale
		{
			get
			{
				throw new NotImplementedException();
			}
			set
			{
				throw new NotImplementedException();
			}
		}

		public Quaternion Rotation
		{
			get
			{
				Quaternion value;
				API_GetRotation(NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetRotation(NativeHandle, ref value);
			}
		}

		public Quaternion GlobalRotation
		{
			get
			{
				throw new NotImplementedException();
			}
			set
			{
				throw new NotImplementedException();
			}
		}

		public Matrix4 LocalMatrix
		{
			get
			{
				Matrix4 value;
				API_GetLocalMatrix(NativeHandle, out value);
				return value;
			}
		}

		public Matrix4 InvertedLocalMatrix
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public Matrix4 GlobalMatrix
		{
			get
			{
				Matrix4 value;
				API_GetGlobalMatrix(NativeHandle, out value);
				return value;
			}
		}

		public Matrix4 InvertedGlobalmatrix
		{
			get
			{
				throw new NotImplementedException();
			}
		}
		
		public int ChildCount
		{
			get
			{
				int value;
				API_GetChildCount(NativeHandle, out value);
				return value;
			}
		}

		public Transform GetChild(int index)
		{
			Transform value;
			API_GetChild(NativeHandle, index, out value);
			return value;
		}

		#endregion

		#region Methods

		// TMP
		public override string ToString()
		{
			return $"Pos: {Position}";
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetParent(IntPtr handle, out Transform parent);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetParent(IntPtr handle, ref Transform parent);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetPosition(IntPtr handle, out Vector3 position);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetPosition(IntPtr handle, ref Vector3 position);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetScale(IntPtr handle, out Vector3 scale);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetScale(IntPtr handle, ref Vector3 scale);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetRotation(IntPtr handle, out Quaternion rotation);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetRotation(IntPtr handle, ref Quaternion rotation);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetLocalMatrix(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetGlobalMatrix(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetChildCount(IntPtr handle, out int count);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetChild(IntPtr handle, int index, out Transform child);


		#endregion
	}
}
