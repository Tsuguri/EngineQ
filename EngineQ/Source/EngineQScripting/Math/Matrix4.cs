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

		public Real M00;
		public Real M01;
		public Real M02;
		public Real M03;
		public Real M10;
		public Real M11;
		public Real M12;
		public Real M13;
		public Real M20;
		public Real M21;
		public Real M22;
		public Real M23;
		public Real M30;
		public Real M31;
		public Real M32;
		public Real M33;

		#endregion

		#region Constructors

		/// <sumary>
		/// Constructs <see cref="Matrix4"/> filled with specified value.
		/// </sumary>
		/// <param name="value">Value to set all elements.</param>
		public Matrix4(Real value)
		{
			this.M00 = value;
			this.M01 = value;
			this.M02 = value;
			this.M03 = value;
			this.M10 = value;
			this.M11 = value;
			this.M12 = value;
			this.M13 = value;
			this.M20 = value;
			this.M21 = value;
			this.M22 = value;
			this.M23 = value;
			this.M30 = value;
			this.M31 = value;
			this.M32 = value;
			this.M33 = value;
		}

		/// <summary>
		/// Constructs Matrix from individual elements.
		/// </summary>
		/// <param name="m00">Element at row 0, column 0.</param>
		/// <param name="m01">Element at row 0, column 1.</param>
		/// <param name="m02">Element at row 0, column 2.</param>
		/// <param name="m03">Element at row 0, column 3.</param>
		/// <param name="m10">Element at row 1, column 0.</param>
		/// <param name="m11">Element at row 1, column 1.</param>
		/// <param name="m12">Element at row 1, column 2.</param>
		/// <param name="m13">Element at row 1, column 3.</param>
		/// <param name="m20">Element at row 2, column 0.</param>
		/// <param name="m21">Element at row 2, column 1.</param>
		/// <param name="m22">Element at row 2, column 2.</param>
		/// <param name="m23">Element at row 2, column 3.</param>
		/// <param name="m30">Element at row 0, column 0.</param>
		/// <param name="m31">Element at row 0, column 1.</param>
		/// <param name="m32">Element at row 0, column 2.</param>
		/// <param name="m33">Element at row 0, column 3.</param>
		public Matrix4(
			Real m00, Real m01, Real m02, Real m03,
			Real m10, Real m11, Real m12, Real m13,
			Real m20, Real m21, Real m22, Real m23,
			Real m30, Real m31, Real m32, Real m33)
		{
			this.M00 = m00;
			this.M01 = m01;
			this.M02 = m02;
			this.M03 = m03;
			this.M10 = m10;
			this.M11 = m11;
			this.M12 = m12;
			this.M13 = m13;
			this.M20 = m20;
			this.M21 = m21;
			this.M22 = m22;
			this.M23 = m23;
			this.M30 = m30;
			this.M31 = m31;
			this.M32 = m32;
			this.M33 = m33;
		}

		/// <summary>
		/// Constructs Matrix from rows.
		/// </summary>
		/// <param name="row0"><see cref="Vector4"/> of elements for first row.</param>
		/// <param name="row1"><see cref="Vector4"/> of elements for second row.</param>
		/// <param name="row2"><see cref="Vector4"/> of elements for third row.</param>
		/// <param name="row3"><see cref="Vector4"/> of elements for fourth row.</param>
		public Matrix4(
			 Vector4 row0,
			 Vector4 row1,
			 Vector4 row2,
			 Vector4 row3)
		{
			this.M00 = row0.X;
			this.M01 = row0.Y;
			this.M02 = row0.Z;
			this.M03 = row0.W;
			this.M10 = row1.X;
			this.M11 = row1.Y;
			this.M12 = row1.Z;
			this.M13 = row1.W;
			this.M20 = row2.X;
			this.M21 = row2.Y;
			this.M22 = row2.Z;
			this.M23 = row2.W;
			this.M30 = row3.X;
			this.M31 = row3.Y;
			this.M32 = row3.Z;
			this.M33 = row3.W;
		}

		#endregion

		#region Properties

		/// <summary>
		///  Provides access to the element at specified row and column.
		/// </summary>
		/// <param name="row">Element row.</param>
		/// <param name="column">Element column.</param>
		/// <returns>Element at specified row and column.</returns>
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

		/// <summary>
		///  Provides access to the element at specified index
		/// </summary>
		/// <param name="index">Element index.</param>
		/// <returns>Element at given index.</returns>
		public Real this[int index]
		{
			get
			{
				switch (index)
				{
					case 0:
						return M00;
					case 1:
						return M01;
					case 2:
						return M02;
					case 3:
						return M03;
					case 4:
						return M10;
					case 5:
						return M11;
					case 6:
						return M12;
					case 7:
						return M13;
					case 8:
						return M20;
					case 9:
						return M21;
					case 10:
						return M22;
					case 11:
						return M23;
					case 12:
						return M30;
					case 13:
						return M31;
					case 14:
						return M32;
					case 15:
						return M33;
					default:
						throw new IndexOutOfRangeException("Invalid index");
				}
			}
			set
			{
				switch (index)
				{
					case 0:
						M00 = value;
						break;
					case 1:
						M01 = value;
						break;
					case 2:
						M02 = value;
						break;
					case 4:
						M10 = value;
						break;
					case 5:
						M11 = value;
						break;
					case 6:
						M12 = value;
						break;
					case 7:
						M13 = value;
						break;
					case 8:
						M20 = value;
						break;
					case 9:
						M21 = value;
						break;
					case 10:
						M22 = value;
						break;
					case 11:
						M23 = value;
						break;
					case 12:
						M30 = value;
						break;
					case 13:
						M31 = value;
						break;
					case 14:
						M32 = value;
						break;
					case 15:
						M33 = value;
						break;
					default:
						throw new IndexOutOfRangeException("Invalid index");
				}
			}
		}

		/// <summary>
		/// Computes determinant of this <see cref="Matrix4"/>.
		/// </summary>
		public Real Determinant
		{
			get
			{
				Real value;
				API_Determinant(ref this, out value);
				return value;
			}
		}

		/// <summary>
		/// Creates new <see cref="Matrix4"/> that is transposition of this one.
		/// </summary>
		public Matrix4 Transposed
		{
			get
			{
				return new Matrix4
				(
					M00, M10, M20, M30,
					M01, M11, M21, M31,
					M02, M12, M22, M32,
					M03, M13, M23, M33
				);
			}
		}

		/// <summary>
		/// Creates new <see cref="Matrix4"/> that is inversion of this one.
		/// </summary>
		public Matrix4 Inverse
		{
			get
			{
				Matrix4 value;
				API_Inversed(ref this, out value);
				return value;
			}
		}

		/// <summary>
		/// <see cref="Vector4"/> of values lying on the diagonal of this <see cref="Matrix4"/>.
		/// </summary>
		public Vector4 Diagonal
		{
			get
			{
				return new Vector4(M00, M11, M22, M33);
			}
			set
			{
				M00 = value.X;
				M11 = value.Y;
				M22 = value.Z;
				M33 = value.W;
			}
		}

		#endregion

		#region Static Properties

		/// <summary>
		/// Identity Matrix.
		/// </summary>
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

		/// <summary>
		/// Modifies this <see cref="Matrix4"/> by transposition.
		/// </summary>
		public void Transpose()
		{
			API_Transpose(ref this);
		}

		/// <summary>
		/// Modifies this <see cref="Matrix4"/> by inversion.
		/// </summary>
		public void Invert()
		{
			this = Inverse;
		}

		/// <summary>
		/// Returns string representation of this <see cref="Matrix4"/>. 
		/// </summary>
		/// <returns>String representation of Matrix.</returns>
		public override string ToString()
		{
			return $"[[{M00},{M01},{M02},{M03}],[{M10},{M11},{M12},{M13}],[{M20},{M21},{M22},{M23}],[{M30},{M31},{M32},{M33}]]";
		}

		/// <summary>
		/// Determines whether the specified object is equal to the current <see cref="Matrix4"/>.
		/// </summary>
		/// <param name="obj">The object to compare with the current <see cref="Matrix4"/>.</param>
		/// <returns>true if the specified object is equal to the current <see cref="Matrix4"/>; otherwise, false.</returns>
		public override bool Equals(object obj)
		{
			if (!(obj is Matrix4))
				return false;

			return this == (Matrix4)obj;
		}

		/// <summary>
		/// Default hash function.
		/// </summary>
		/// <returns>Default hash value.</returns>
		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		/// <summary>
		/// <see cref="Vector4"/> representing one of columns of this <see cref="Matrix4"/>.
		/// </summary>
		/// <param name="column">Index of column.</param>
		/// <returns><see cref="Vector4"/> representing column.</returns>
		public Vector4 GetColumn(int column)
		{
			return new Vector4(this[0, column], this[1, column], this[2, column], this[3, column]);
		}

		/// <summary>
		/// Sets content of <paramref name="column"/> with given <see cref="Vector4"/> <paramref name="value"/>.
		/// </summary>
		/// <param name="column">Index of the column to set.</param>
		/// <param name="value"><see cref="Vector4"/> of values to set in the column.</param>
		public void SetColumn(int column, Vector4 value)
		{
			this[0, column] = value.X;
			this[1, column] = value.Y;
			this[2, column] = value.Z;
			this[3, column] = value.W;
		}

		/// <summary>
		/// <see cref="Vector4"/> representing one of rows of this <see cref="Matrix4"/>.
		/// </summary>
		/// <param name="row">Index of row.</param>
		/// <returns><see cref="Vector4"/> representing row.</returns>
		public Vector4 GetRow(int row)
		{
			return new Vector4(this[row, 0], this[row, 1], this[row, 2], this[row, 3]);
		}

		/// <summary>
		/// Sets content fo <paramref name="row"/>  with given <see cref="Vector4"/> <paramref name="value"/>.
		/// </summary>
		/// <param name="row">Index of the row to set.</param>
		/// <param name="value"><see cref="Vector4"/> of values to set in the row.</param>
		public void SetRow(int row, Vector4 value)
		{
			this[row, 0] = value.X;
			this[row, 1] = value.Y;
			this[row, 2] = value.Z;
			this[row, 3] = value.W;
		}

		/// <summary>
		/// Converts this <see cref="Matrix4"/> into <see cref="Vector4"/>s of rows.
		/// </summary>
		/// <returns><see cref="Vector4"/> array of rows.</returns>
		public Vector4[] GetRows()
		{
			return new Vector4[4]
			{
				new Vector4(M00, M01, M02, M03),
				new Vector4(M10, M11, M12, M13),
				new Vector4(M20, M21, M22, M23),
				new Vector4(M30, M31, M32, M33)
			};
		}

		/// <summary>
		/// Converts this <see cref="Matrix4"/> into <see cref="Vector4"/>s of columns.
		/// </summary>
		/// <returns><see cref="Vector4"/> array of columns.</returns>
		public Vector4[] GetColumns()
		{
			return new Vector4[4]
			{
				new Vector4(M00, M10, M20, M30),
				new Vector4(M01, M11, M21, M31),
				new Vector4(M02, M12, M22, M32),
				new Vector4(M03, M13, M23, M33)
			};
		}

		#endregion

		#region Static Methods

		/// <summary>
		/// Creates <see cref="Matrix4"/> from given <see cref="Vector4"/>s representing rows.
		/// </summary>
		/// <param name="row0">First row.</param>
		/// <param name="row1">Second row.</param>
		/// <param name="row2">Third row.</param>
		/// <param name="row3">Fourth row.</param>
		/// <returns><see cref="Matrix4"/> created from given columns.</returns>
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

		/// <summary>
		/// Creates <see cref="Matrix4"/> from given <see cref="Vector4"/>s representing columns.
		/// </summary>
		/// <param name="column0">First column.</param>
		/// <param name="column1">Second column.</param>
		/// <param name="column2">Third column.</param>
		/// <param name="column3">Fourth column.</param>
		/// <returns><see cref="Matrix4"/> created from given rows.</returns>
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

		/// <summary>
		/// Creates rotation <see cref="Matrix4"/> from given <see cref="Quaternion"/> rotation.
		/// </summary>
		/// <param name="q">Rotation.</param>
		/// <returns>Constructed rotation matrix.</returns>
		public static Matrix4 CreateRotation(Quaternion q)
		{
			Matrix4 value;
			API_CreateRotation(ref q, out value);
			return value;
		}

		/// <summary>
		/// Creates translation matrix by given coordinates.
		/// </summary>
		/// <param name="x">Translation on the X axis.</param>
		/// <param name="y">Translation on the Y axis.</param>
		/// <param name="z">Translation on the Z axis.</param>
		/// <returns>Constructed translation matrix.</returns>
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

		/// <summary>
		/// Creates translation matrix by given vector.
		/// </summary>
		/// <param name="translation">Translation vector.</param>
		/// <returns>Constructed translation matrix.</returns>
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

		/// <summary>
		/// Creates scale matrix by given scalars.
		/// </summary>
		/// <param name="x">Scale on the X axis.</param>
		/// <param name="y">Scale on the Y axis.</param>
		/// <param name="z">Scale on the Z axis.</param>
		/// <returns>Constructed scale matrix.</returns>
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

		/// <summary>
		/// Creates scale matrix by given <see cref="Vector3"/> of scalars.
		/// </summary>
		/// <param name="scale"><see cref="Vector3"/> of scalars.</param>
		/// <returns>Constructed scale matrix.</returns>
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

		/// <summary>
		/// Creates rotation matrix representing rotation by given angle around X axis.
		/// </summary>
		/// <param name="angle">Rotation in radians around X axis.</param>
		/// <returns>Constructed rotation matrix.</returns>
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

		/// <summary>
		/// Creates rotation matrix representing rotation by given angle around Y axis.
		/// </summary>
		/// <param name="angle">Rotation in radians around Y axis.</param>
		/// <returns>Constructed rotation matrix.</returns>
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

		/// <summary>
		/// Creates rotation matrix representing rotation by given angle around Z axis.
		/// </summary>
		/// <param name="angle">Rotation in radians around Z axis.</param>
		/// <returns>Constructed rotation matrix.</returns>
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

		/// <summary>
		/// Creates viewport transformation.
		/// </summary>
		/// <param name="x">X coordinate of the upper left corner of the viewport.</param>
		/// <param name="y">Y coordinate of the upper left corner of the viewport.</param>
		/// <param name="width">With of the viewport.</param>
		/// <param name="height">Height of the viewport.</param>
		/// <returns>Constructed viewport transformation matrix.</returns>
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

		/// <summary>
		/// Creates frustum perspective transformation.
		/// </summary>
		/// <param name="fovy">Field of view in radians.</param>
		/// <param name="aspect">Aspect ratio.</param>
		/// <param name="near">Near plane distance.</param>
		/// <param name="far">Far plane distance.</param>
		/// <returns>Constructed perspective transformation matrix.</returns>
		public static Matrix4 CreateFrustum(Real fovY, Real aspectRatio, Real near, Real far)
		{
			Matrix4 value;
			API_CreateFrustum(fovY, aspectRatio, near, far, out value);
			return value;
		}

		/// <summary>
		/// Creates rotation matrix that rotates forward vector to point in the direction pointing from <paramref name="cameraPosition"/> to <paramref name="cameraTarget"/>.
		/// </summary>
		/// <param name="cameraPosition">Position of the observer.</param>
		/// <param name="cameraTarget">Point at which ovserver will be looking after transformation.</param>
		/// <param name="upVector">Up direction vector.</param>
		/// <returns></returns>
		public static Matrix4 CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 upVector)
		{
			Matrix4 value;
			API_CreateLookAt(ref cameraPosition, ref cameraTarget, ref upVector, out value);
			return value;
		}

		/// <summary>
		/// Applies matrix transformation to direction vector.
		/// </summary>
		/// <param name="matrix">Transformation matrix.</param>
		/// <param name="vector">Direction vector.</param>
		/// <returns>Transformed direction vector.</returns>
		public static Vector3 TransformVector(Matrix4 matrix, Vector3 vector)
		{
			Vector3 value;
			API_TransformVector(ref matrix, ref vector, out value);
			return value;
		}

		/// <summary>
		/// Applies matrix transformation to position stored in vector.
		/// </summary>
		/// <param name="matrix">Transformation matrix.</param>
		/// <param name="position">Position vector.</param>
		/// <returns>Transformed position vector.</returns>
		public static Vector3 TransformPosition(Matrix4 matrix, Vector3 position)
		{
			Vector3 value;
			API_TransformPosition(ref matrix, ref position, out value);
			return value;
		}

		/// <summary>
		/// Applies matrix transformation to normal vector.
		/// </summary>
		/// <param name="matrix">Transformation matrix.</param>
		/// <param name="normal">Normal vector.</param>
		/// <returns>Transformed normal vector.</returns>
		public static Vector3 TransformNormal(Matrix4 matrix, Vector3 normal)
		{
			Vector3 value;
			API_TransformNormal(ref matrix, ref normal, out value);
			return value;
		}

		/// <summary>
		/// Applies matrix transformation to given position stored in vector applying perspective division.
		/// </summary>
		/// <param name="matrix">Transformation matrix.</param>
		/// <param name="position">Position vector.</param>
		/// <returns>Transformed position vector.</returns>
		public static Vector3 TransformPerspective(Matrix4 matrix, Vector3 position)
		{
			Vector3 value;
			API_TransformPerspective(ref matrix, ref position, out value);
			return value;
		}

		#endregion

		#region Operators

		/// <summary>
		/// Converts specified <see cref="Matrix4"/> to <see cref="Matrix3"/>.
		/// </summary>
		/// <param name="matrix"><see cref="Matrix4"/> to be converted to <see cref="Matrix3"/>.</param>
		public static explicit operator Matrix3(Matrix4 matrix)
		{
			return new Matrix3
			(
				matrix.M00, matrix.M01, matrix.M02,
				matrix.M10, matrix.M11, matrix.M12,
				matrix.M20, matrix.M21, matrix.M22
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
				-matrix.M00, -matrix.M01, -matrix.M02, -matrix.M03,
				-matrix.M10, -matrix.M11, -matrix.M12, -matrix.M13,
				-matrix.M20, -matrix.M21, -matrix.M22, -matrix.M23,
				-matrix.M30, -matrix.M31, -matrix.M32, -matrix.M33
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

		public static bool operator ==(Matrix4 matrix1, Matrix4 matrix2)
		{
			bool value;
			API_Equal(ref matrix1, ref matrix2, out value);
			return value;
		}

		public static bool operator !=(Matrix4 matrix1, Matrix4 matrix2)
		{
			bool value;
			API_NotEqual(ref matrix1, ref matrix2, out value);
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

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Equal(ref Matrix4 lhs, ref Matrix4 rhs, out bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_NotEqual(ref Matrix4 lhs, ref Matrix4 rhs, out bool value);

		#endregion
	}
}