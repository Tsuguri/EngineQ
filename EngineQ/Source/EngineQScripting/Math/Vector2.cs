using System;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Type = System.Single;
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2
	{
		#region Fields

		public Type X;
		public Type Y;

		#endregion

		#region Constructors

		public Vector2(Type value)
		{
			this.X = value;
			this.Y = value;
		}

		public Vector2(Type x, Type y)
		{
			this.X = x;
			this.Y = y;
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
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}
		}

		public Type Sum
		{
			get
			{
				return this.X + this.Y;
			}
		}

		public Real Length
		{
			get
			{
				return (Real)System.Math.Sqrt((double)(this.X * this.X + this.Y * this.Y));
			}
		}

		public Type LengthSquared
		{
			get
			{
				return this.X * this.X + this.Y * this.Y;
			}
		}

		public Vector2 Normalized
		{
			get
			{
				Vector2 ret = this;
				ret.Normalize();

				return ret;
			}
		}

		#endregion

		#region Static Properties

		public static Vector2 Zero
		{
			get
			{
				return new Vector2((Type)0, (Type)0);
			}
		}

		public static Vector2 One
		{
			get
			{
				return new Vector2((Type)1, (Type)1);
			}
		}

		public static Vector2 Left
		{
			get
			{
				return new Vector2((Type)(-1), (Type)0);
			}
		}

		public static Vector2 Right
		{
			get
			{
				return new Vector2((Type)1, (Type)0);
			}
		}

		public static Vector2 Up
		{
			get
			{
				return new Vector2((Type)0, (Type)1);
			}
		}

		public static Vector2 Down
		{
			get
			{
				return new Vector2((Type)0, (Type)(-1));
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
		}

		public override string ToString()
		{
			return $"[{this.X},{this.Y}]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Vector2))
				return false;

			return this == (Vector2)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion

		#region Static Methods

		public static Type DistanceSquared(Vector2 vector1, Vector2 vector2)
		{
			return (vector2 - vector1).LengthSquared;
		}

		public static Real Distance(Vector2 vector1, Vector2 vector2)
		{
			return (vector2 - vector1).Length;
		}

		public static Type DotProduct(Vector2 vector1, Vector2 vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y;
		}

		#endregion

		#region Operators

		//public explicit operator Vector2d()
		//{
		//	return Vector2<Type2>((Type2)this.X, (Type2)this.Y);
		//}

		public static Vector2 operator -(Vector2 vector)
		{
			return new Vector2(-vector.X, -vector.Y);
		}

		public static Vector2 operator +(Vector2 vector)
		{
			return vector;
		}

		public static Vector2 operator +(Vector2 vector1, Vector2 vector2)
		{
			return new Vector2(vector1.X + vector2.X, vector1.Y + vector2.Y);
		}

		public static Vector2 operator -(Vector2 vector1, Vector2 vector2)
		{
			return new Vector2(vector1.X - vector2.X, vector1.Y - vector2.Y);
		}

		public static Vector2 operator *(Vector2 vector, Type scalar)
		{
			return new Vector2(vector.X * scalar, vector.Y * scalar);
		}

		public static Vector2 operator *(Type scalar, Vector2 vector)
		{
			return new Vector2(scalar * vector.X, scalar * vector.Y);
		}

		public static Vector2 operator *(Vector2 vector1, Vector2 vector2)
		{
			return new Vector2(vector1.X * vector2.X, vector1.Y * vector2.Y);
		}

		public static Vector2 operator /(Vector2 vector, Type scalar)
		{
			return new Vector2(vector.X / scalar, vector.Y / scalar);
		}

		public static Vector2 operator /(Vector2 vector1, Vector2 vector2)
		{
			return new Vector2(vector1.X / vector2.X, vector1.Y / vector2.Y);
		}

		public static bool operator ==(Vector2 vector1, Vector2 vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y);
		}

		public static bool operator !=(Vector2 vector1, Vector2 vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y);
		}

		#endregion
	}
}
