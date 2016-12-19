using System;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Type = System.Single;
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Vector4
	{
		#region Fields

		public Type X;
		public Type Y;
		public Type Z;
		public Type W;

		#endregion

		#region Constructors

		public Vector4(Type value)
		{
			this.X = value;
			this.Y = value;
			this.Z = value;
			this.W = value;
		}

		public Vector4(Type x, Type y, Type z, Type w)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
			this.W = w;
		}

		public Vector4(Vector2 vector, Type z, Type w)
		{
			this.X = vector.X;
			this.Y = vector.Y;
			this.Z = z;
			this.W = w;
		}

		public Vector4(Vector3 vector, Type w)
		{
			this.X = vector.X;
			this.Y = vector.Y;
			this.Z = vector.Z;
			this.W = w;
		}

		#endregion

		#region Properties

		public Type this[int index]
		{
			get
			{
				switch (index)
				{
					case 0:
					return this.X;
					case 1:
					return this.Y;
					case 2:
					return this.Z;
					case 3:
					return this.W;
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}

			set
			{
				switch (index)
				{
					case 0:
					this.X = value;
					return;
					case 1:
					this.Y = value;
					return;
					case 2:
					this.Z = value;
					return;
					case 3:
					this.W = value;
					return;
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}
		}

		public Type Sum
		{
			get
			{
				return this.X + this.Y + this.Z + this.W;
			}
		}

		public Real Length
		{
			get
			{
				return (Real)System.Math.Sqrt((double)(this.X * this.X + this.Y * this.Y + this.Z * this.Z + this.W * this.W));
			}
		}

		public Type LengthSquared
		{
			get
			{
				return this.X * this.X + this.Y * this.Y + this.Z * this.Z + this.W * this.W;
			}
		}

		public Vector4 Normalized
		{
			get
			{
				Vector4 ret = this;
				ret.Normalize();

				return ret;
			}
		}

		#endregion

		#region Static Properties

		public static Vector4 Zero
		{
			get
			{
				return new Vector4((Type)0, (Type)0, (Type)0, (Type)0);
			}
		}

		public static Vector4 One
		{
			get
			{
				return new Vector4((Type)1, (Type)1, (Type)1, (Type)1);
			}
		}

		#endregion

		#region Methods

		public void Normalize()
		{
			Type length = (Type)Length;

			if (length == (Type)0)
				return;

			this.X /= length;
			this.Y /= length;
			this.Z /= length;
			this.W /= length;
		}

		public override string ToString()
		{
			return $"[{this.X},{this.Y},{this.Z},{this.W}]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Vector4))
				return false;

			return this == (Vector4)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion

		#region Static Methods

		public static Type DistanceSquared(Vector4 vector1, Vector4 vector2)
		{
			return (vector2 - vector1).LengthSquared;
		}

		public static Real Distance(Vector4 vector1, Vector4 vector2)
		{
			return (vector2 - vector1).Length;
		}

		#endregion

		#region Operators

		public static explicit operator Vector2(Vector4 vector)
		{
			return new Vector2(vector.X, vector.Y);
		}

		public static explicit operator Vector3(Vector4 vector)
		{
			return new Vector3(vector.X, vector.Y, vector.Z);
		}

		//public static explicit operator Vector4(Vector4 vector)
		//{
		//	return new Vector4((MType)vector.X, (MType)vector.Y, (MType)vector.Z, (MType)vector.W);
		//}

		public static explicit operator Vector4f(Vector4 vector)
		{
			return new Vector4f((float)vector.X, (float)vector.Y, (float)vector.Z, (float)vector.W);
		}

		public static explicit operator Vector4d(Vector4 vector)
		{
			return new Vector4d((double)vector.X, (double)vector.Y, (double)vector.Z, (double)vector.W);
		}

		public static explicit operator Vector4i(Vector4 vector)
		{
			return new Vector4i((int)vector.X, (int)vector.Y, (int)vector.Z, (int)vector.W);
		}



		public static Vector4 operator -(Vector4 vector)
		{
			return new Vector4(-vector.X, -vector.Y, -vector.Z, -vector.W);
		}

		public static Vector4 operator +(Vector4 vector)
		{
			return vector;
		}

		public static Vector4 operator +(Vector4 vector1, Vector4 vector2)
		{
			return new Vector4(vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z, vector1.W + vector2.W);
		}

		public static Vector4 operator -(Vector4 vector1, Vector4 vector2)
		{
			return new Vector4(vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z, vector1.W - vector2.W);
		}

		public static Vector4 operator *(Vector4 vector, Type scalar)
		{
			return new Vector4(vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar);
		}

		public static Vector4 operator *(Type scalar, Vector4 vector)
		{
			return new Vector4(scalar * vector.X, scalar * vector.Y, scalar * vector.Z, scalar * vector.W);
		}

		public static Vector4 operator *(Vector4 vector1, Vector4 vector2)
		{
			return new Vector4(vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z, vector1.W * vector2.W);
		}

		public static Vector4 operator /(Vector4 vector, Type scalar)
		{
			return new Vector4(vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar);
		}

		public static Vector4 operator /(Vector4 vector1, Vector4 vector2)
		{
			return new Vector4(vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z, vector1.W / vector2.W);
		}

		public static bool operator ==(Vector4 vector1, Vector4 vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z && vector1.W == vector2.W);
		}

		public static bool operator !=(Vector4 vector1, Vector4 vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z || vector1.W != vector2.W);
		}

		#endregion
	}
}
