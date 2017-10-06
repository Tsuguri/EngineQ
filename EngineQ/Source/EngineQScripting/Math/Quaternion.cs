using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;

namespace EngineQ.Math
{
	using Real = System.Single;

	/// <summary>
	/// Represents rotation if form of Quaternion. 
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct Quaternion
	{
		#region Fields

		/// <summary>
		/// W component of <see cref="Quaternion"/>.
		/// </summary>
		public Real W;

		/// <summary>
		/// X component of <see cref="Quaternion"/>.
		/// </summary>
		public Real X;

		/// <summary>
		/// Y component of <see cref="Quaternion"/>.
		/// </summary>
		public Real Y;

		/// <summary>
		/// Z component of <see cref="Quaternion"/>.
		/// </summary>
		public Real Z;

		#endregion

		#region Constructors

		public Quaternion(Real w, Real x, Real y, Real z)
		{
			this.W = w;
			this.X = x;
			this.Y = y;
			this.Z = z;
		}

		#endregion

		#region Properties

		/// <summary>
		/// Direction of Axis around which rotation occurs.
		/// </summary>
		public Vector4 AxisAngle
		{
			get
			{
				Vector4 value;
				API_GetAxisAngle(ref this, out value);
				return value;
			}
		}

		/// <summary>
		/// Euler angles representation of quaternion's rotation.
		/// </summary>
		public Vector3 EulerAngles
		{
			get
			{
				Vector3 value;
				API_GetEulerAngles(ref this, out value);
				return value;
			}
		}

		/// <summary>
		/// Squared lenght of quaternion.
		/// </summary>
		public Real LengthSquared
		{
			get
			{
				return this.W * this.W + this.X * this.X + this.Y * this.Y + this.Z * this.Z;
			}
		}

		/// <summary>
		/// Length of quaternion (sum of all components to power of two).
		/// </summary>
		public Real Length
		{
			get
			{
				return (Real)System.Math.Sqrt((double)(this.W * this.W + this.X * this.X + this.Y * this.Y + this.Z * this.Z));
			}
		}

		/// <summary>
		/// Normalized quaternion - all coponents divided by Z component.
		/// </summary>
		public Quaternion Normalized
		{
			get
			{
				Quaternion ret = this;
				ret.Normalize();

				return ret;
			}
		}

		#endregion

		#region Static Properties

		/// <summary>
		/// Quaternion representing no rotation.
		/// </summary>
		public static Quaternion Identity
		{
			get
			{
				return new Quaternion((Real)1, (Real)0, (Real)0, (Real)0);
			}
		}

		#endregion

		#region Methods

		/// <summary>
		/// Normalizes quaternion - divides all components by Z component.
		/// </summary>
		public void Normalize()
		{
			API_Normalize(ref this);
		}

		public override string ToString()
		{
			return $"[{this.W},{this.X},{this.Y},{this.Z}]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Quaternion))
				return false;

			return this == (Quaternion)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion

		#region Static Methods

		/// <summary>
		/// Creates <see cref="Quaternion"/> from rotation around given axis by given angle.
		/// </summary>
		/// <param name="axis">Axis around which rotation occurs.</param>
		/// <param name="angle">Angle of rotation. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation equal to given.</returns>
		public static Quaternion CreateFromAxisAngle(Vector3 axis, Real angle)
		{
			return CreateFromAxisAngle(axis.X, axis.Y, axis.Z, angle);
		}

		/// <summary>
		/// Creates <see cref="Quaternion"/> from rotation around given axis by given angle.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="angle">Angle of rotation. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation equal to given.</returns>
		public static Quaternion CreateFromAxisAngle(Real x, Real y, Real z, Real angle)
		{
			Quaternion ret;
			API_CreateFromAxisAngle(x, y, z, angle, out ret);
			return ret;
		}

		/// <summary>
		/// Creates rotation around Z axis by given angle.
		/// </summary>
		/// <param name="angle">Value of angle around Z axis. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateRotationZ(Real angle)
		{
			Quaternion ret;
			API_CreateRotationZ(angle, out ret);
			return ret;
		}

		/// <summary>
		/// Creates rotation around Y axis by given angle.
		/// </summary>
		/// <param name="angle">Value of angle around Y axis. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateRotationY(Real angle)
		{
			Quaternion ret;
			API_CreateRotationY(angle, out ret);
			return ret;
		}

		/// <summary>
		/// Creates rotation around X axis by given angle.
		/// </summary>
		/// <param name="angle">Value of angle around X axis. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateRotationX(Real angle)
		{
			Quaternion ret;
			API_CreateRotationX(angle, out ret);
			return ret;
		}

		/// <summary>
		/// Creates rotation equal to rotation represented by Euler angles given in radians.
		/// </summary>
		/// <param name="x">Rotation around X axis.</param>
		/// <param name="y">Rotation around Y axis.</param>
		/// <param name="z">Rotation around Z axis.</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateFromEuler(Real x, Real y, Real z)
		{
			Quaternion ret;
			API_CreateFromEuler(x, y, z, out ret);
			return ret;
		}

		/// <summary>
		/// Creates rotation equal to rotation represented by Euler angles given in radians.
		/// </summary>
		/// <param name="angles">Vector of rotations around axes. In radians.</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateFromEuler(Vector3 angles)
		{
			return CreateFromEuler(angles.X, angles.Y, angles.Z);
		}

		/// <summary>
		/// Creates <see cref="Quaternion"/> representing rotation from no-rotation state to looking at given <paramref name="targetPoint"/> from <paramref name="sourcePoint"/>.
		/// </summary>
		/// <param name="sourcePoint">Position of object.</param>
		/// <param name="targetPoint">Target that will be targeted by rotation</param>
		/// <param name="up">Vector representing up vector - orthogonal to axis from source to target point</param>
		/// <returns><see cref="Quaternion"/> representing rotation.</returns>
		public static Quaternion CreateLookAt(Vector3 sourcePoint, Vector3 targetPoint, Vector3 up)
        {
			Quaternion ret;
			API_CreateLookAt(ref sourcePoint, ref targetPoint, ref up, out ret);
			return ret;
        }

        #endregion

        #region Static Operators

        public static Quaternion operator +(Quaternion q)
		{
			return q;
		}

		public static Quaternion operator -(Quaternion q)
		{
			Quaternion q2 = q.Normalized;
			return new Quaternion(q2.W, -q2.X, -q2.Y, -q2.Z);
		}

		public static Quaternion operator +(Quaternion q1, Quaternion q2)
		{
			return new Quaternion(q1.W + q2.W, q1.X + q2.X, q1.Y + q2.Y, q1.Z + q2.Z);
		}

		public static Quaternion operator -(Quaternion q1, Quaternion q2)
		{
			return new Quaternion(q1.W - q2.W, q1.X - q2.X, q1.Y - q2.Y, q1.Z - q2.Z);
		}

		public static Quaternion operator *(Quaternion q1, Quaternion q2)
		{
			Quaternion ret;
			API_MultiplyQuaternion(ref q1, ref q2, out ret);
			return ret;
		}

		public static Vector4 operator *(Quaternion q, Vector4 v)
		{
			Vector4 ret;
			API_MultiplyVector4(ref q, ref v, out ret);
			return ret;
		}

		public static Vector3 operator *(Quaternion q, Vector3 v)
		{
			Vector3 ret;
			API_MultiplyVector3(ref q, ref v, out ret);
			return ret;
		}

		public static bool operator ==(Quaternion q1, Quaternion q2)
		{
			return (q1.W == q2.W && q1.X == q2.X && q1.Y == q2.Y && q1.Z == q2.Z);
		}

		public static bool operator !=(Quaternion q1, Quaternion q2)
		{
			return (q1.W != q2.W || q1.X != q2.X || q1.Y != q2.Y || q1.Z != q2.Z);
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetEulerAngles(ref Quaternion quaternion, out Vector3 eulerAngles);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetAxisAngle(ref Quaternion quaternion, out Vector4 axisAngle);
		
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Normalize(ref Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateFromAxisAngle(Real x, Real y, Real z, Real angle, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateRotationX(Real angle, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateRotationY(Real angle, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateRotationZ(Real angle, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateFromEuler(Real x, Real y, Real z, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateLookAt(ref Vector3 sourcePoint, ref Vector3 targetPoint, ref Vector3 up, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyQuaternion(ref Quaternion q1, ref Quaternion q2, out Quaternion quaternion);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyVector4(ref Quaternion q, ref Vector4 v, out Vector4 vector);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyVector3(ref Quaternion q, ref Vector3 v, out Vector3 vector);

		#endregion
	}
}
