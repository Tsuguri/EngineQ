using System;
using System.Runtime.CompilerServices;

namespace EngineQ
{
	using Math;

	/// <summary>
	/// Automatically created <see cref="Component"/> of <see cref="Entity"/>. Cannot be removed. Transforms are kept in tree structure.
	/// </summary>
	public sealed class Transform : Component
	{
		#region Properties

		/// <summary>
		/// Parent <see cref="Transform"/> in tree structure.
		/// </summary>
		public Transform Parent
		{
			get
			{
				Transform value;
				API_GetParent(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetParent(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Position of object relational to <see cref="Transform.Parent"/>'s position (and rotation!)
		/// </summary>
		public Vector3 Position
		{
			get
			{
				Vector3 value;
				API_GetPosition(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetPosition(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Global space object position.
		/// </summary>
		public Vector3 GlobalPosition
		{
			get
			{
				Vector3 value;
				API_GetGlobalPosition(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetGlobalPosition(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Object's scale
		/// </summary>
		public Vector3 Scale
		{
			get
			{
				Vector3 value;
				API_GetScale(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetScale(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Object rotation relational to <see cref="Transform.Parent"/>'s rotation
		/// </summary>
		public Quaternion Rotation
		{
			get
			{
				Quaternion value;
				API_GetRotation(this.NativeHandle, out value);
				return value;
			}

			set
			{
				API_SetRotation(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Object rotation in global space.
		/// </summary>
		public Quaternion GlobalRotation
		{
			get
			{
				Quaternion value;
				API_GetGlobalRotation(this.NativeHandle, out value);
				return value;
			}
			set
			{
				API_SetGlobalRotation(this.NativeHandle, ref value);
			}
		}

		/// <summary>
		/// Matrix representing object <see cref="Transform.Position"/>, <see cref="Transform.Rotation"/> and <see cref="Transform.Scale"/> relational to <see cref="Transform.Parent"/>
		/// </summary>
		public Matrix4 LocalMatrix
		{
			get
			{
				Matrix4 value;
				API_GetLocalMatrix(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Inversion of <see cref="Transform.LocalMatrix"/>
		/// </summary>
		public Matrix4 LocalMatrixInverse
		{
			get
			{
				Matrix4 value;
				API_GetLocalMatrixInverse(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Matrix representing object position, rotation and scale in world space.
		/// </summary>
		public Matrix4 GlobalMatrix
		{
			get
			{
				Matrix4 value;
				API_GetGlobalMatrix(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Inversion of <see cref="Transform.GlobalMatrix"/>
		/// </summary>
		public Matrix4 GlobalMatrixInverse
		{
			get
			{
				Matrix4 value;
				API_GetGlobalMatrixInverse(this.NativeHandle, out value);
				return value;
			}
		}
		
		/// <summary>
		/// Number of other <see cref="Transform"/>s that are childs of this <see cref="Transform"/>
		/// </summary>
		public int ChildCount
		{
			get
			{
				int value;
				API_GetChildCount(this.NativeHandle, out value);
				return value;
			}
		}

		/// <summary>
		/// Finds child of this <see cref="Transform"/> with given index
		/// </summary>
		/// <param name="index">Index of child to find. From 0 to <see cref="ChildCount"/></param>
		/// <returns></returns>
		public Transform GetChild(int index)
		{
			Transform value;
			API_GetChild(this.NativeHandle, index, out value);
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
		private static extern void API_GetGlobalPosition(IntPtr handle, out Vector3 position);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetGlobalPosition(IntPtr handle, ref Vector3 position);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetScale(IntPtr handle, out Vector3 scale);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetScale(IntPtr handle, ref Vector3 scale);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetRotation(IntPtr handle, out Quaternion rotation);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetRotation(IntPtr handle, ref Quaternion rotation);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetGlobalRotation(IntPtr handle, out Quaternion rotation);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetGlobalRotation(IntPtr handle, ref Quaternion rotation);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetLocalMatrix(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetLocalMatrixInverse(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetGlobalMatrix(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetGlobalMatrixInverse(IntPtr handle, out Matrix4 matrix);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetChildCount(IntPtr handle, out int count);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetChild(IntPtr handle, int index, out Transform child);
		
		#endregion
	}
}
