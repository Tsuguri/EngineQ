using System;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Type = System.Int32;
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2i
	{
		#region Fields

		public Type X;
		public Type Y;

		#endregion

		#region Constructors

		public Vector2i(Type value)
		{
			this.X = value;
			this.Y = value;
		}

		public Vector2i(Type x, Type y)
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
		
		#endregion

		#region Static Properties

		public static Vector2i Zero
		{
			get
			{
				return new Vector2i((Type)0, (Type)0);
			}
		}

		public static Vector2i One
		{
			get
			{
				return new Vector2i((Type)1, (Type)1);
			}
		}

		public static Vector2i Left
		{
			get
			{
				return new Vector2i((Type)(-1), (Type)0);
			}
		}

		public static Vector2i Right
		{
			get
			{
				return new Vector2i((Type)1, (Type)0);
			}
		}

		public static Vector2i Up
		{
			get
			{
				return new Vector2i((Type)0, (Type)1);
			}
		}

		public static Vector2i Down
		{
			get
			{
				return new Vector2i((Type)0, (Type)(-1));
			}
		}

		#endregion

		#region Methods
		
		public override string ToString()
		{
			return $"[{this.X},{this.Y}]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Vector2i))
				return false;

			return this == (Vector2i)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion

		#region Static Methods

		public static Type DistanceSquared(Vector2i vector1, Vector2i vector2)
		{
			return (vector2 - vector1).LengthSquared;
		}

		public static Real Distance(Vector2i vector1, Vector2i vector2)
		{
			return (vector2 - vector1).Length;
		}

		public static Type DotProduct(Vector2i vector1, Vector2i vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y;
		}

		#endregion

		#region Operators

		public static explicit operator Vector2(Vector2i vector)
		{
			return new Vector2((Real)vector.X, (Real)vector.Y);
		}

		public static Vector2i operator -(Vector2i vector)
		{
			return new Vector2i(-vector.X, -vector.Y);
		}

		public static Vector2i operator +(Vector2i vector)
		{
			return vector;
		}

		public static Vector2i operator +(Vector2i vector1, Vector2i vector2)
		{
			return new Vector2i(vector1.X + vector2.X, vector1.Y + vector2.Y);
		}

		public static Vector2i operator -(Vector2i vector1, Vector2i vector2)
		{
			return new Vector2i(vector1.X - vector2.X, vector1.Y - vector2.Y);
		}

		public static Vector2i operator *(Vector2i vector, Type scalar)
		{
			return new Vector2i(vector.X * scalar, vector.Y * scalar);
		}

		public static Vector2i operator *(Type scalar, Vector2i vector)
		{
			return new Vector2i(scalar * vector.X, scalar * vector.Y);
		}

		public static Vector2i operator *(Vector2i vector1, Vector2i vector2)
		{
			return new Vector2i(vector1.X * vector2.X, vector1.Y * vector2.Y);
		}

		public static Vector2i operator /(Vector2i vector, Type scalar)
		{
			return new Vector2i(vector.X / scalar, vector.Y / scalar);
		}

		public static Vector2i operator /(Vector2i vector1, Vector2i vector2)
		{
			return new Vector2i(vector1.X / vector2.X, vector1.Y / vector2.Y);
		}

		public static bool operator ==(Vector2i vector1, Vector2i vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y);
		}

		public static bool operator !=(Vector2i vector1, Vector2i vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y);
		}

		#endregion
	}
}
