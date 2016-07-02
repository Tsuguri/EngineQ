using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace EngineQ.Math
{
	using Real = System.Single;

	[StructLayout(LayoutKind.Sequential)]
	public struct Matrix4
	{
		#region Fields

		public Real m00;
		public Real m01;
		public Real m02;
		public Real m03;
		public Real m10;
		public Real m11;
		public Real m12;
		public Real m13;
		public Real m20;
		public Real m21;
		public Real m22;
		public Real m23;
		public Real m30;
		public Real m31;
		public Real m32;
		public Real m33;

		#endregion

		#region Constructors

		public Matrix4(Real value)
		{
			this.m00 = value;
			this.m01 = value;
			this.m02 = value;
			this.m03 = value;
			this.m10 = value;
			this.m11 = value;
			this.m12 = value;
			this.m13 = value;
			this.m20 = value;
			this.m21 = value;
			this.m22 = value;
			this.m23 = value;
			this.m30 = value;
			this.m31 = value;
			this.m32 = value;
			this.m33 = value;
		}

		public Matrix4(
			Real m00, Real m01, Real m02, Real m03,
			Real m10, Real m11, Real m12, Real m13,
			Real m20, Real m21, Real m22, Real m23,
			Real m30, Real m31, Real m32, Real m33)
		{
			this.m00 = m00;
			this.m01 = m01;
			this.m02 = m02;
			this.m03 = m03;
			this.m10 = m10;
			this.m11 = m11;
			this.m12 = m12;
			this.m13 = m13;
			this.m20 = m20;
			this.m21 = m21;
			this.m22 = m22;
			this.m23 = m23;
			this.m30 = m30;
			this.m31 = m31;
			this.m32 = m32;
			this.m33 = m33;
		}

		public Matrix4(
			 Vector4 row0,
			 Vector4 row1,
			 Vector4 row2,
			 Vector4 row3)
		{
			this.m00 = row0.X;
			this.m01 = row0.Y;
			this.m02 = row0.Z;
			this.m03 = row0.W;
			this.m10 = row1.X;
			this.m11 = row1.Y;
			this.m12 = row1.Z;
			this.m13 = row1.W;
			this.m20 = row2.X;
			this.m21 = row2.Y;
			this.m22 = row2.Z;
			this.m23 = row2.W;
			this.m30 = row3.X;
			this.m31 = row3.Y;
			this.m32 = row3.Z;
			this.m33 = row3.W;
		}

		#endregion

		#region Properties

		public Real this[int row, int column]
		{
			get
			{
				return this[row * 4 + column];
			}
			set
			{
				this[row * 4 + column] = value;
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
					return m03;
					case 4:
					return m10;
					case 5:
					return m11;
					case 6:
					return m12;
					case 7:
					return m13;
					case 8:
					return m20;
					case 9:
					return m21;
					case 10:
					return m22;
					case 11:
					return m23;
					case 12:
					return m30;
					case 13:
					return m31;
					case 14:
					return m32;
					case 15:
					return m33;
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
					case 4:
					m10 = value;
					break;
					case 5:
					m11 = value;
					break;
					case 6:
					m12 = value;
					break;
					case 7:
					m13 = value;
					break;
					case 8:
					m20 = value;
					break;
					case 9:
					m21 = value;
					break;
					case 10:
					m22 = value;
					break;
					case 11:
					m23 = value;
					break;
					case 12:
					m30 = value;
					break;
					case 13:
					m31 = value;
					break;
					case 14:
					m32 = value;
					break;
					case 15:
					m33 = value;
					break;
					default:
					throw new IndexOutOfRangeException("Invalid index");
				}
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

		public Matrix4 Transposed
		{
			get
			{
				return new Matrix4
				(
					m00, m10, m20, m30,
					m01, m11, m21, m31,
					m02, m12, m22, m32,
					m03, m13, m23, m33
				);
			}
		}

		public Matrix4 Inversed
		{
			get
			{
				Matrix4 value;
				API_Inversed(ref this, out value);
				return value;
			}
		}

		public Vector4 Diagonal
		{
			get
			{
				return new Vector4(m00, m11, m22, m33);
			}
			set
			{
				m00 = value.X;
				m11 = value.Y;
				m22 = value.Z;
				m33 = value.W;
			}
		}

		#endregion

		#region Static Properties

		public static Matrix4 Identity
		{
			get
			{
				return new Matrix4
				(
					(Real)1, (Real)0, (Real)0, (Real)0,
					(Real)0, (Real)1, (Real)0, (Real)0,
					(Real)0, (Real)0, (Real)1, (Real)0,
					(Real)0, (Real)0, (Real)0, (Real)1
				);
			}
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
			return $"[[{m00},{m01},{m02},{m03}],[{m10},{m11},{m12},{m13}],[{m20},{m21},{m22},{m23}],[{m30},{m31},{m32},{m33}]]";
		}

		public Vector4 GetColumn(int column)
		{
			return new Vector4(this[0, column], this[1, column], this[2, column], this[3, column]);
		}

		public void SetColumn(int column, Vector4 value)
		{
			this[0, column] = value.X;
			this[1, column] = value.Y;
			this[2, column] = value.Z;
			this[3, column] = value.W;
		}

		public Vector4 GetRow(int row)
		{
			return new Vector4(this[row, 0], this[row, 1], this[row, 2], this[row, 3]);
		}

		public void SetRow(int row, Vector4 value)
		{
			this[row, 0] = value.X;
			this[row, 1] = value.Y;
			this[row, 2] = value.Z;
			this[row, 3] = value.W;
		}

		public Vector4[] GetRows()
		{
			return new Vector4[4]
			{
				new Vector4(m00, m01, m02, m03),
				new Vector4(m10, m11, m12, m13),
				new Vector4(m20, m21, m22, m23),
				new Vector4(m30, m31, m32, m33)
			};
		}

		public Vector4[] GetColumns()
		{
			return new Vector4[4]
			{
				new Vector4(m00, m10, m20, m30),
				new Vector4(m01, m11, m21, m31),
				new Vector4(m02, m12, m22, m32),
				new Vector4(m03, m13, m23, m33)
			};
		}

		#endregion

		#region Static Methods

		public static Matrix4 CreateFromRows(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3)
		{
			return new Matrix4
			(
				row0.X, row0.Y, row0.Z, row0.W,
				row1.X, row1.Y, row1.Z, row1.W,
				row2.X, row2.Y, row2.Z, row2.W,
				row3.X, row3.Y, row3.Z, row3.W
			);
		}

		public static Matrix4 CreateFromColumns(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3)
		{
			return new Matrix4
			(
				column0.X, column1.X, column2.X, column3.X,
				column0.Y, column1.Y, column2.Y, column3.Y,
				column0.Z, column1.Z, column2.Z, column3.Z,
				column0.W, column1.W, column2.W, column3.W
			);
		}

		public static Matrix4 CreateRotation(Quaternion q)
		{
			Matrix4 value;
			API_CreateRotation(ref q, out value);
			return value;
		}

		public static Matrix4 CreateTranslation(Real x, Real y, Real z)
		{
			return new Matrix4
			(
				(Real)1, (Real)0, (Real)0, x,
				(Real)0, (Real)1, (Real)0, y,
				(Real)0, (Real)0, (Real)1, z,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateTranslation(Vector3 translation)
		{
			return new Matrix4
			(
				(Real)1, (Real)0, (Real)0, translation.X,
				(Real)0, (Real)1, (Real)0, translation.Y,
				(Real)0, (Real)0, (Real)1, translation.Z,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateScale(Real x, Real y, Real z)
		{
			return new Matrix4
			(
				x, (Real)0, (Real)0, (Real)0,
				(Real)0, y, (Real)0, (Real)0,
				(Real)0, (Real)0, z, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateScale(Vector3 scale)
		{
			return new Matrix4
			(
				scale.X, (Real)0, (Real)0, (Real)0,
				(Real)0, scale.Y, (Real)0, (Real)0,
				(Real)0, (Real)0, scale.Z, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateRotationX(Real angle)
		{
			Real s = (Real)System.Math.Sin((double)angle);
			Real c = (Real)System.Math.Cos((double)angle);

			return new Matrix4
			(
				(Real)1, (Real)0, (Real)0, (Real)0,
				(Real)0, c, -s, (Real)0,
				(Real)0, s, c, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateRotationY(Real angle)
		{
			Real s = (Real)System.Math.Sin((double)angle);
			Real c = (Real)System.Math.Cos((double)angle);

			return new Matrix4
			(
				c, (Real)0, s, (Real)0,
				(Real)0, (Real)1, (Real)0, (Real)0,
				-s, (Real)0, c, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateRotationZ(Real angle)
		{
			Real s = (Real)System.Math.Sin((double)angle);
			Real c = (Real)System.Math.Cos((double)angle);

			return new Matrix4
			(
				c, -s, (Real)0, (Real)0,
					  s, c, (Real)0, (Real)0,
				(Real)0, (Real)0, (Real)1, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateViewport(Real x, Real y, Real width, Real height)
		{
			return new Matrix4
			(
				width, (Real)0, (Real)0, x,
				(Real)0, height, (Real)0, y,
				(Real)0, (Real)0, (Real)1, (Real)0,
				(Real)0, (Real)0, (Real)0, (Real)1
			);
		}

		public static Matrix4 CreateFrustum(Real fovy, Real aspect, Real near, Real far)
		{
			Matrix4 value;
			API_CreateFrustum(fovy, aspect, near, far, out value);
			return value;
		}

		public static Matrix4 CreateLookAt(Vector3 cameraPosition, Vector3  cameraTarget, Vector3  upVector)
		{
			Matrix4 value;
			API_CreateLookAt(ref cameraPosition, ref cameraTarget, ref upVector, out value);
			return value;
		}

		public static Vector3 TransformVector(Matrix4 matrix, Vector3 vector)
		{
			Vector3 value;
			API_TransformVector(ref matrix, ref vector, out value);
			return value;
		}

		public static Vector3 TransformPosition(Matrix4 matrix, Vector3 position)
		{
			Vector3 value;
			API_TransformPosition(ref matrix, ref position, out value);
			return value;
		}

		public static Vector3 TransformNormal(Matrix4 matrix, Vector3 normal)
		{
			Vector3 value;
			API_TransformNormal(ref matrix, ref normal, out value);
			return value;
		}

		public static Vector3 TransformPerspective(Matrix4 matrix, Vector3 vector)
		{
			Vector3 value;
			API_TransformPerspective(ref matrix, ref vector, out value);
			return value;
		}

		#endregion

		#region Operators

		public static explicit operator Matrix3(Matrix4 matrix)
		{
			return new Matrix3
			(
				matrix.m00, matrix.m01, matrix.m02,
				matrix.m10, matrix.m11, matrix.m12,
				matrix.m20, matrix.m21, matrix.m22
			);
		}

		public static Matrix4 operator +(Matrix4 matrix)
		{
			return matrix;
		}

		public static Matrix4 operator -(Matrix4 matrix)
		{
			return new Matrix4
			(
				-matrix.m00, -matrix.m01, -matrix.m02, -matrix.m03,
				-matrix.m10, -matrix.m11, -matrix.m12, -matrix.m13,
				-matrix.m20, -matrix.m21, -matrix.m22, -matrix.m23,
				-matrix.m30, -matrix.m31, -matrix.m32, -matrix.m33
			);
		}

		public static Matrix4 operator +(Matrix4 matrix1, Matrix4 matrix2)
		{
			Matrix4 value;
			API_AddMatrix(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static Matrix4 operator -(Matrix4 matrix1, Matrix4 matrix2)
		{
			Matrix4 value;
			API_SubtractMatrix(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static Matrix4 operator *(Matrix4 matrix, Real scalar)
		{
			Matrix4 value;
			API_MultiplyScalar(ref matrix, scalar, out value);
			return value;
		}

		public static Matrix4 operator *(Real scalar, Matrix4 matrix)
		{
			Matrix4 value;
			API_MultiplyScalar(ref matrix, scalar, out value);
			return value;
		}

		public static Vector4 operator *(Matrix4 matrix, Vector4 vector)
		{
			Vector4 value;
			API_MultiplyVector4(ref matrix, ref vector, out value);
			return value;
		}

		public static Matrix4 operator *(Matrix4 matrix1, Matrix4 matrix2)
		{
			Matrix4 value;
			API_MultiplyMatrix(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static Matrix4 operator /(Matrix4 matrix, Real scalar)
		{
			Matrix4 value;
			API_DivideScalar(ref matrix, scalar, out value);
			return value;
		}

		#endregion

		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Determinant(ref Matrix4 matrix, out Real value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Inversed(ref Matrix4 matrix, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Transpose(ref Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateRotation(ref Quaternion quaternion, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateFrustum(Real fovy, Real aspect, Real near, Real far, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_CreateLookAt(ref Vector3 cameraPosition, ref Vector3 cameraTarget, ref Vector3 upVector, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_TransformVector(ref Matrix4 matrix, ref Vector3 vector, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_TransformPosition(ref Matrix4 matrix, ref Vector3 position, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_TransformNormal(ref Matrix4 matrix, ref Vector3 normal, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_TransformPerspective(ref Matrix4 matrix, ref Vector3 vector, out Vector3 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_AddMatrix(ref Matrix4 lhs, ref Matrix4 rhs, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SubtractMatrix(ref Matrix4 lhs, ref Matrix4 rhs, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyScalar(ref Matrix4 lhs, Real scalar, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyVector4(ref Matrix4 lhs, ref Vector4 rhs, out Vector4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_MultiplyMatrix(ref Matrix4 lhs, ref Matrix4 rhs, out Matrix4 value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_DivideScalar(ref Matrix4 lhs, Real rhs, out Matrix4 value);

		#endregion
	}
}