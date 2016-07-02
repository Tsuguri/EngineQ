using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Matrix3
	{
		#region Fields

		public Real m00;
		public Real m01;
		public Real m02;
		public Real m10;
		public Real m11;
		public Real m12;
		public Real m20;
		public Real m21;
		public Real m22;

		#endregion

		#region Constructors

		public Matrix3(
			Real m00, Real m01, Real m02,
			Real m10, Real m11, Real m12,
			Real m20, Real m21, Real m22)
		{
			this.m00 = m00;
			this.m01 = m01;
			this.m02 = m02;
			this.m10 = m10;
			this.m11 = m11;
			this.m12 = m12;
			this.m20 = m20;
			this.m21 = m21;
			this.m22 = m22;
		}

		public Matrix3(Vector3 row0, Vector3 row1, Vector3 row2)
		{
			this.m00 = row0.X;
			this.m01 = row0.Y;
			this.m02 = row0.Z;
			this.m10 = row1.X;
			this.m11 = row1.Y;
			this.m12 = row1.Z;
			this.m20 = row2.X;
			this.m21 = row2.Y;
			this.m22 = row2.Z;

		}

		#endregion

		#region Properties

		public Real this[int row, int column]
		{
			get
			{
				return this[row * 3 + column];
			}
			set
			{
				this[row * 3 + column] = value;
			}
		}

		public Real this[int index]
		{
			get
			{
				switch (index)
				{
					case 0:
					return m00;
					case 1:
					return m01;
					case 2:
					return m02;
					case 3:
					return m10;
					case 4:
					return m11;
					case 5:
					return m12;
					case 6:
					return m20;
					case 7:
					return m21;
					case 8:
					return m22;
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}
			set
			{
				switch (index)
				{
					case 0:
					m00 = value;
					break;
					case 1:
					m01 = value;
					break;
					case 2:
					m02 = value;
					break;
					case 3:
					m10 = value;
					break;
					case 4:
					m11 = value;
					break;
					case 5:
					m12 = value;
					break;
					case 6:
					m20 = value;
					break;
					case 7:
					m21 = value;
					break;
					case 8:
					m22 = value;
					break;
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
			}
		}

		public Matrix3 Transposed
		{
			get
			{
				return new Matrix3(m00, m10, m20, m01, m11, m21, m02, m12, m22);
			}
		}

		public Matrix3 Inversed
		{
			get
			{
				Matrix3 value;
				API_Inverse(ref this, out value);
				return value;
			}
		}

		public Real Determinant
		{
			get
			{
				Real value;
				API_Determinant(ref this, out value);
				return value;
			}
		}

		public Vector3 Diagonal
		{
			get
			{
				return new Vector3(m00, m11, m22);
			}

			set
			{
				m00 = value.X;
				m11 = value.Y;
				m22 = value.Z;
			}
		}

		#endregion

		#region Static Properties

		public static Matrix3 GetIdentity()
		{
			return new Matrix3(
				(Real)1, (Real)0, (Real)0,
				(Real)0, (Real)1, (Real)0,
				(Real)0, (Real)0, (Real)1);
		}

		#endregion

		#region Methods

		public void Transpose()
		{
			API_Transpose(ref this);
		}

		public void Inverse()
		{
			this = Inversed;
		}

		public override string ToString()
		{
			return $"[[{m00},{m01},{m02}],[{m10},{m11},{m12}],[{m20},{m21},{m22}]]";
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Matrix3))
				return false;

			return this == (Matrix3)obj;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		public Vector3 GetColumn(int column)
		{
			return new Vector3(this[0, column], this[1, column], this[2, column]);
		}

		public void SetColumn(int column, Vector3 value)
		{
			this[0, column] = value.X;
			this[1, column] = value.Y;
			this[2, column] = value.Z;
		}

		public Vector3 GetRow(int row)
		{
			return new Vector3(this[row, 0], this[row, 1], this[row, 2]);
		}

		public void SetRow(int row, Vector3 value)
		{
			this[row, 0] = value.X;
			this[row, 1] = value.Y;
			this[row, 2] = value.Z;
		}

		public Vector3[] GetRows()
		{
			return new Vector3[3]
			{
				new Vector3(m00, m01, m02),
				new Vector3(m10, m11, m12),
				new Vector3(m20, m21, m22)
			};
		}

		public Vector3[] GetColumns()
		{
			return new Vector3[3]
			{
				new Vector3(m00, m10, m20),
				new Vector3(m01, m11, m21),
				new Vector3(m02, m12, m22)
			};
		}

		#endregion

		#region Static Methods

		public static Matrix3 CreateFromColumns(Vector3 column0, Vector3 column1, Vector3 column2)
		{
			return new Matrix3
			(
				column0.X, column1.X, column2.X,
				column0.Y, column1.Y, column2.Y,
				column0.Z, column1.Z, column2.Z
			);
		}

		public static Matrix3 CreateFromRows(Vector3 row0, Vector3 row1, Vector3 row2)
		{
			return new Matrix3
			(
				row0.X, row0.Y, row0.Z,
				row1.X, row1.Y, row1.Z,
				row2.X, row2.Y, row2.Z
			);
		}

		#endregion

		#region Operators

		public static Matrix3 operator *(Matrix3 matrix1, Matrix3 matrix2)
		{
			Matrix3 value;
			API_MultiplyMatrix(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static Vector3 operator *(Matrix3 matrix, Vector3 vector)
		{
			Vector3 value;
			API_MultiplyVector3(ref matrix, ref vector, out value);
			return value;
		}

		public static Matrix3 operator *(Matrix3 matrix, Real scalar)
		{
			Matrix3 value;
			API_MultiplyScalar(ref matrix, scalar, out value);
			return value;
		}

		public static Matrix3 operator *(Real scalar, Matrix3 matrix)
		{
			Matrix3 value;
			API_MultiplyScalar(ref matrix, scalar, out value);
			return value;
		}

		public static Matrix3 operator /(Matrix3 matrix, Real scalar)
		{
			Matrix3 value;
			API_DivideScalar(ref matrix, scalar, out value);
			return value;
		}

		public static bool operator ==(Matrix3 matrix1, Matrix3 matrix2)
		{
			bool value;
			API_Equal(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static bool operator !=(Matrix3 matrix1, Matrix3 matrix2)
		{
			bool value;
			API_NotEqual(ref matrix1, ref matrix2, out value);
			return value;
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Inverse(ref Matrix3 matrix, out Matrix3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Determinant(ref Matrix3 matrix, out Real value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Transpose(ref Matrix3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyMatrix(ref Matrix3 lhs, ref Matrix3 rhs, out Matrix3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyVector3(ref Matrix3 lhs, ref Vector3 rhs, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyScalar(ref Matrix3 lhs, Real rhs, out Matrix3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_DivideScalar(ref Matrix3 lhs, Real rhs, out Matrix3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Equal(ref Matrix3 lhs, ref Matrix3 rhs, out bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_NotEqual(ref Matrix3 lhs, ref Matrix3 rhs, out bool value);

		#endregion
	}
}
