using System;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Type = System.Single;
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3
	{
		#region Fields

		public Type X;
		public Type Y;
		public Type Z;

		#endregion

		#region Constructors

		public Vector3(Type value)
		{
			this.X = value;
			this.Y = value;
			this.Z = value;
		}

		public Vector3(Type x, Type y, Type z)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
		}

		public Vector3(Vector2 vector, Type z)
		{
			this.X = vector.X;
			this.Y = vector.Y;
			this.Z = z;
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
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}
		}

		public Type Sum
		{
			get
			{
				return this.X + this.Y + this.Z;
			}
		}

		public Real Length
		{
			get
			{
				return (Real)System.Math.Sqrt((double)(this.X * this.X + this.Y * this.Y + this.Z * this.Z));
			}
		}

		public Type LengthSquared
		{
			get
			{
				return this.X * this.X + this.Y * this.Y + this.Z * this.Z;
			}
		}

		public Vector3 Normalized
		{
			get
			{
				Vector3 ret = this;
				ret.Normalize();

				return ret;
			}
		}

		#endregion

		#region Static Properties

		public static Vector3 Zero
		{
			get
			{
				return new Vector3((Type)0, (Type)0, (Type)0);
			}
		}

		public static Vector3 One
		{
			get
			{
				return new Vector3((Type)1, (Type)1, (Type)1);
			}
		}

		public static Vector3 Left
		{
			get
			{
				return new Vector3((Type)(-1), (Type)0, (Type)0);
			}
		}

		public static Vector3 Right
		{
			get
			{
				return new Vector3((Type)1, (Type)0, (Type)0);
			}
		}

		public static Vector3 Up
		{
			get
			{
				return new Vector3((Type)0, (Type)1, (Type)0);
			}
		}

		public static Vector3 Down
		{
			get
			{
				return new Vector3((Type)0, (Type)(-1), (Type)0);
			}
		}

		public static Vector3 Forward
		{
			get
			{
				return new Vector3((Type)0, (Type)0, (Type)1);
			}
		}

		public static Vector3 Back
		{
			get
			{
				return new Vector3((Type)0, (Type)0, (Type)(-1));
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
		}

		public override string ToString()
		{
			return $"[{this.X},{this.Y},{this.Z}]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Vector3))
				return false;

			return this == (Vector3)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion

		#region Static Methods

		public static Type DistanceSquared(Vector3 vector1, Vector3 vector2)
		{
			return (vector2 - vector1).LengthSquared;
		}

		public static Real Distance(Vector3 vector1, Vector3 vector2)
		{
			return (vector2 - vector1).Length;
		}

		public static Type DotProduct(Vector3 vector1, Vector3 vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		public static Vector3 CrossProduct(Vector3 vector1, Vector3 cector2)
		{
			return new Vector3(vector1.Y * cector2.Z - cector2.Y * vector1.Z, vector1.Z * cector2.X - cector2.Z * vector1.X, vector1.X * cector2.Y - cector2.X * vector1.Y);
		}

		#endregion

		#region Operators

		public static explicit operator Vector2(Vector3 vector)
		{
			return new Vector2(vector.X, vector.Y);
		}

		//public static explicit operator Vector3(Vector3 vector)
		//{
		//	return new Vector3((Mtype)vector.X, (Mtype)vector.Y, (Mtype)vector.Z);
		//}

		public static explicit operator Vector3f(Vector3 vector)
		{
			return new Vector3f((float)vector.X, (float)vector.Y, (float)vector.Z);
		}

		public static explicit operator Vector3d(Vector3 vector)
		{
			return new Vector3d((double)vector.X, (double)vector.Y, (double)vector.Z);
		}

		public static explicit operator Vector3i(Vector3 vector)
		{
			return new Vector3i((int)vector.X, (int)vector.Y, (int)vector.Z);
		}



		public static Vector3 operator -(Vector3 vector)
		{
			return new Vector3(-vector.X, -vector.Y, -vector.Z);
		}

		public static Vector3 operator +(Vector3 vector)
		{
			return vector;
		}

		public static Vector3 operator +(Vector3 vector1, Vector3 vector2)
		{
			return new Vector3(vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z);
		}

		public static Vector3 operator -(Vector3 vector1, Vector3 vector2)
		{
			return new Vector3(vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z);
		}

		public static Vector3 operator *(Vector3 vector, Type scalar)
		{
			return new Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
		}

		public static Vector3 operator *(Type scalar, Vector3 vector)
		{
			return new Vector3(scalar * vector.X, scalar * vector.Y, scalar * vector.Z);
		}

		public static Vector3 operator *(Vector3 vector1, Vector3 vector2)
		{
			return new Vector3(vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z);
		}

		public static Vector3 operator /(Vector3 vector, Type scalar)
		{
			return new Vector3(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
		}

		public static Vector3 operator /(Vector3 vector1, Vector3 vector2)
		{
			return new Vector3(vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z);
		}

		public static bool operator ==(Vector3 vector1, Vector3 vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z);
		}

		public static bool operator !=(Vector3 vector1, Vector3 vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z);
		}

		#endregion
	}
}
