#ifndef ENGINEQ_MATH_MATRIX4_HPP
#define ENGINEQ_MATH_MATRIX4_HPP

// This project
#include "Types.hpp"
#include "EngineQCommon/Utilities/StringHelpers.hpp"


namespace EngineQ
{
	namespace Math
	{
		struct Matrix4
		{
#pragma region Fields

			union
			{
				Real Values[16] = { static_cast<Real>(0) };
				Real Values2[4][4];
				struct
				{
					Real M00, M01, M02, M03;
					Real M10, M11, M12, M13;
					Real M20, M21, M22, M23;
					Real M30, M31, M32, M33;
				};
			};

#pragma endregion

#pragma region Constructors

			/// <sumary>
			/// Constructs empty <see cref="Matrix4"/> filled with zeros.
			/// </sumary>
			explicit Matrix4() = default;

			/// <sumary>
			/// Constructs <see cref="Matrix4"/> filled with specified value.
			/// </sumary>
			/// <param name="value">Value to set all elements.</param>
			explicit Matrix4(Real value);

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
			explicit Matrix4(
				Real m00, Real m01, Real m02, Real m03,
				Real m10, Real m11, Real m12, Real m13,
				Real m20, Real m21, Real m22, Real m23,
				Real m30, Real m31, Real m32, Real m33);

			/// <summary>
			/// Constructs Matrix from rows.
			/// </summary>
			/// <param name="row0"><see cref="Vector4"/> of elements for first row.</param>
			/// <param name="row1"><see cref="Vector4"/> of elements for second row.</param>
			/// <param name="row2"><see cref="Vector4"/> of elements for third row.</param>
			/// <param name="row3"><see cref="Vector4"/> of elements for fourth row.</param>
			explicit Matrix4(
				const Vector4& row0,
				const Vector4& row1,
				const Vector4& row2,
				const Vector4& row3);

#pragma endregion

#pragma region Methods

			/// <summary>
			/// Modifies this <see cref="Matrix4"/> by transposition.
			/// </summary>
			void Transpose();

			/// <summary>
			/// Modifies this <see cref="Matrix4"/> by inversion.
			/// </summary>
			void Inverse();

			/// <summary>
			/// Returns string representation of this <see cref="Matrix4"/>. 
			/// </summary>
			/// <returns>String representation of <see cref="Matrix4"/>.</returns>
			std::string ToString() const;

			/// <summary>
			/// Computes and returns determinant of this <see cref="Matrix4"/>.
			/// </summary>
			/// <returns>Determinant of this <see cref="Matrix4"/>.</returns>
			Real GetDeterminant() const;

			/// <summary>
			/// Returns new <see cref="Matrix4"/> that is transposition of this one.
			/// </summary>
			/// <returns><see cref="Matrix4"/> that is transposition of this one.</returns>
			Matrix4 GetTransposed() const;

			/// <summary>
			/// Returns new <see cref="Matrix4"/> that is inversion of this one.
			/// </summary>
			/// <returns> <see cref="Matrix4"/> that is inversion of this one.</returns>
			Matrix4 GetInversed() const;

			/// <summary>
			/// Returns <see cref="Vector4"/> of values lying on the diagonal of this <see cref="Matrix4"/>.
			/// </summary>
			/// <returns><see cref="Vector4"/> of values lying on the diagonal of this <see cref="Matrix4"/>.</returns>
			Vector4 GetDiagonal() const;

			/// <summary>
			/// Sets values lying on the diagonal of this <see cref="Matrix4"/>.
			/// </summary>
			/// <param name="diagonal"><see cref="Vector4"/> of elements to set as diagonal.</param>
			void SetDiagonal(const Vector4& diagonal);

			/// <summary>
			/// <see cref="Vector4"/> representing one of columns of this <see cref="Matrix4"/>.
			/// </summary>
			/// <param name="column">Index of column.</param>
			/// <returns><see cref="Vector4"/> representing column.</returns>
			Vector4 GetColumn(std::size_t column) const;

			/// <summary>
			/// Sets content of <paramref name="column"/> with given <see cref="Vector4"/> <paramref name="value"/>.
			/// </summary>
			/// <param name="column">Index of column to set.</param>
			/// <param name="value">New values.</param>
			void SetColumn(std::size_t column, const Vector4& value);

			/// <summary>
			/// <see cref="Vector4"/> representing one of rows of this <see cref="Matrix4"/>.
			/// </summary>
			/// <param name="row">Index of row.</param>
			/// <returns><see cref="Vector4"/> representing row.</returns>
			Vector4 GetRow(std::size_t row) const;

			/// <summary>
			/// Sets content fo <paramref name="row"/>  with given <see cref="Vector4"/> <paramref name="value"/>.
			/// </summary>
			/// <param name="row">Index of the row to set.</param>
			/// <param name="value"><see cref="Vector4"/> of values to set in the row.</param>
			void SetRow(std::size_t row, const Vector4& value);

			/// <summary>
			/// Extracts this <see cref="Matrix3"/>'s rows into given <see cref="Vector3"/>s references. 
			/// </summary>
			/// <param name="row0">Reference to the <see cref="Vector4"/> that will contain values from first row.</param>
			/// <param name="row1">Reference to the <see cref="Vector4"/> that will contain values from second row.</param>
			/// <param name="row2">Reference to the <see cref="Vector4"/> that will contain values from third row.</param>
			/// <param name="row3">Reference to the <see cref="Vector4"/> that will contain values from fourth row.</param>
			void GetRows(Vector4& row0, Vector4& row1, Vector4& row2, Vector4& row3) const;

			/// <summary>
			/// Extracts this <see cref="Matrix3"/>'s columns into given <see cref="Vector3"/>s references. 
			/// </summary>
			/// <param name="column0">Reference to the <see cref="Vector4"/> that will contain values from first column.</param>
			/// <param name="column1">Reference to the <see cref="Vector4"/> that will contain values from second column.</param>
			/// <param name="column2">Reference to the <see cref="Vector4"/> that will contain values from third column.</param>
			/// <param name="column3">Reference to the <see cref="Vector4"/> that will contain values from fourth column.</param>
			void GetColumns(Vector4& column0, Vector4& column1, Vector4& column2, Vector4& column3) const;

#pragma endregion

#pragma region Static Methods

			/// <summary>
			/// Returns identity Matrix.
			/// </summary>
			/// <returns>Identity Matrix.</returns>
			static Matrix4 GetIdentity();

			/// <summary>
			/// Creates <see cref="Matrix4"/> from given <see cref="Vector4"/>s representing rows.
			/// </summary>
			/// <param name="row0">First row.</param>
			/// <param name="row1">Second row.</param>
			/// <param name="row2">Third row.</param>
			/// <param name="row3">Fourth row.</param>
			/// <returns><see cref="Matrix4"/> created from given columns.</returns>
			static Matrix4 CreateFromRows(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

			/// <summary>
			/// Creates <see cref="Matrix4"/> from given <see cref="Vector4"/>s representing columns.
			/// </summary>
			/// <param name="column0">First column.</param>
			/// <param name="column1">Second column.</param>
			/// <param name="column2">Third column.</param>
			/// <param name="column3">Fourth column.</param>
			/// <returns><see cref="Matrix4"/> created from given rows.</returns>
			static Matrix4 CreateFromColumns(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);

			/// <summary>
			/// Creates rotation <see cref="Matrix4"/> from given <see cref="Quaternion"/> rotation.
			/// </summary>
			/// <param name="q">Rotation.</param>
			/// <returns>Constructed rotation matrix.</returns>
			static Matrix4 CreateRotation(const Quaternion& q);

			/// <summary>
			/// Creates translation matrix by given coordinates.
			/// </summary>
			/// <param name="x">Translation on the X axis.</param>
			/// <param name="y">Translation on the Y axis.</param>
			/// <param name="z">Translation on the Z axis.</param>
			/// <returns>Constructed translation matrix.</returns>
			static Matrix4 CreateTranslation(Real x, Real y, Real z);

			/// <summary>
			/// Creates translation matrix by given vector.
			/// </summary>
			/// <param name="translation">Translation vector.</param>
			/// <returns>Constructed translation matrix.</returns>
			static Matrix4 CreateTranslation(const Vector3& translation);

			/// <summary>
			/// Creates scale matrix by given scalars.
			/// </summary>
			/// <param name="x">Scale on the X axis.</param>
			/// <param name="y">Scale on the Y axis.</param>
			/// <param name="z">Scale on the Z axis.</param>
			/// <returns>Constructed scale matrix.</returns>
			static Matrix4 CreateScale(Real x, Real y, Real z);

			/// <summary>
			/// Creates scale matrix by given <see cref="Vector3"/> of scalars.
			/// </summary>
			/// <param name="scale"><see cref="Vector3"/> of scalars.</param>
			/// <returns>Constructed scale matrix.</returns>
			static Matrix4 CreateScale(const Vector3& scale);

			/// <summary>
			/// Creates rotation matrix representing rotation by given angle around X axis.
			/// </summary>
			/// <param name="angle">Rotation in radians around X axis.</param>
			/// <returns>Constructed rotation matrix.</returns>
			static Matrix4 CreateRotationX(Real angle);

			/// <summary>
			/// Creates rotation matrix representing rotation by given angle around Y axis.
			/// </summary>
			/// <param name="angle">Rotation in radians around Y axis.</param>
			/// <returns>Constructed rotation matrix.</returns>
			static Matrix4 CreateRotationY(Real angle);

			/// <summary>
			/// Creates rotation matrix representing rotation by given angle around Z axis.
			/// </summary>
			/// <param name="angle">Rotation in radians around Z axis.</param>
			/// <returns>Constructed rotation matrix.</returns>
			static Matrix4 CreateRotationZ(Real angle);

			/// <summary>
			/// Creates viewport transformation.
			/// </summary>
			/// <param name="x">X coordinate of the upper left corner of the viewport.</param>
			/// <param name="y">Y coordinate of the upper left corner of the viewport.</param>
			/// <param name="width">With of the viewport.</param>
			/// <param name="height">Height of the viewport.</param>
			/// <returns>Constructed viewport transformation matrix.</returns>
			static Matrix4 CreateViewport(Real x, Real y, Real width, Real height);

			/// <summary>
			/// Creates frustum perspective transformation.
			/// </summary>
			/// <param name="fovy">Field of view in radians.</param>
			/// <param name="aspect">Aspect ratio.</param>
			/// <param name="near">Near plane distance.</param>
			/// <param name="far">Far plane distance.</param>
			/// <returns>Constructed perspective transformation matrix.</returns>
			static Matrix4 CreateFrustum(Real fovy, Real aspect, Real near, Real far);

			/// <summary>
			/// Creates ortographic perspective transformation.
			/// </summary>
			/// <param name="left">Distance to the left plane.</param>
			/// <param name="right">Distance to the right plane.</param>
			/// <param name="bottom">Distance to the bottom plane.</param>
			/// <param name="top">Distance to the top plane.</param>
			/// <param name="near">Distance to the near plane.</param>
			/// <param name="far">Distance to the far plane.</param>
			/// <returns>Constructed perspective transformation matrix.</returns>
			static Matrix4 CreateOrtho(Real left, Real right, Real bottom, Real top, Real near, Real far);

			/// <summary>
			/// Creates rotation matrix that rotates forward vector to point in the direction pointing from <paramref name="cameraPosition"/> to <paramref name="cameraTarget"/>.
			/// </summary>
			/// <param name="cameraPosition">Position of the observer.</param>
			/// <param name="cameraTarget">Point at which ovserver will be looking after transformation.</param>
			/// <param name="upVector">Up direction vector.</param>
			/// <returns></returns>
			static Matrix4 CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& upVector);

			/// <summary>
			/// Applies matrix transformation to direction vector.
			/// </summary>
			/// <param name="matrix">Transformation matrix.</param>
			/// <param name="vector">Direction vector.</param>
			/// <returns>Transformed direction vector.</returns>
			static Vector3 TransformVector(const Matrix4& matrix, const Vector3& vector);

			/// <summary>
			/// Applies matrix transformation to position stored in vector.
			/// </summary>
			/// <param name="matrix">Transformation matrix.</param>
			/// <param name="position">Position vector.</param>
			/// <returns>Transformed position vector.</returns>
			static Vector3 TransformPosition(const Matrix4& matrix, const Vector3& position);

			/// <summary>
			/// Applies matrix transformation to normal vector.
			/// </summary>
			/// <param name="matrix">Transformation matrix.</param>
			/// <param name="normal">Normal vector.</param>
			/// <returns>Transformed normal vector.</returns>
			static Vector3 TransformNormal(const Matrix4& matrix, const Vector3& normal);

			/// <summary>
			/// Applies matrix transformation to given position stored in vector applying perspective division.
			/// </summary>
			/// <param name="matrix">Transformation matrix.</param>
			/// <param name="position">Position vector.</param>
			/// <returns>Transformed position vector.</returns>
			static Vector3 TransformPerspective(const Matrix4& matrix, const Vector3& position);

#pragma endregion

#pragma region Operators

			/// <summary>
			/// Converts this <see cref="Matrix4"/> to <see cref="Matrix3"/>.
			/// </summary>
			/// <returns><see cref="Matrix3"/> containing upper 3x3 matrix of this <see cref="Matrix4"/>.</returns>
			explicit operator Matrix3() const;

			void operator += (const Matrix4& matrix);
			void operator -= (const Matrix4& matrix);
			void operator *= (Real scalar);
			void operator /= (Real scalar);
			void operator *= (const Matrix4& matrix);

			/// <summary>
			///  Provides access to the element at specified index.
			/// </summary>
			/// <param name="index">Element index.</param>
			/// <returns>Element at given index.</returns>
			Real operator () (std::size_t index) const;

			/// <summary>
			///  Provides access to the element at specified index.
			/// </summary>
			/// <param name="index">Element index.</param>
			/// <returns>Reference to the element at given index.</returns>
			Real& operator () (std::size_t index);

			/// <summary>
			///  Provides access to the element at specified index
			/// </summary>
			/// <param name="index">Element index.</param>
			/// <returns>Element at given index.</returns>
			Real operator [] (std::size_t index) const;

			/// <summary>
			///  Provides access to the element at specified index.
			/// </summary>
			/// <param name="index">Element index.</param>
			/// <returns>Reference to the element at given index.</returns>
			Real& operator [] (std::size_t index);

			/// <summary>
			///  Provides access to the element at specified row and column.
			/// </summary>
			/// <param name="row">Element row.</param>
			/// <param name="column">Element column.</param>
			/// <returns>Element at specified row and column.</returns>
			Real operator () (std::size_t row, std::size_t column) const;

			/// <summary>
			/// Provides access to the element at specified row and column.
			/// </summary>
			/// <param name="row">Element row.</param>
			/// <param name="column">Element column.</param>
			/// <returns>Reference to the element at specified row and column.</returns>
			Real& operator () (std::size_t row, std::size_t column);

#pragma endregion
		};

#pragma region Static Operators

		Matrix4 operator + (const Matrix4& matrix);
		Matrix4 operator - (const Matrix4& matrix);
		Matrix4 operator + (const Matrix4& lhs, const Matrix4& rhs);
		Matrix4 operator - (const Matrix4& lhs, const Matrix4& rhs);
		Matrix4 operator * (const Matrix4& matrix, Real scalar);
		Matrix4 operator * (Real scalar, const Matrix4& matrix);
		Vector4 operator * (const Matrix4& lhs, const Vector4& rhs);
		Matrix4 operator * (const Matrix4& lhs, const Matrix4& rhs);
		Matrix4 operator / (const Matrix4& matrix, Real scalar);

		bool operator == (const Matrix4& lhs, const Matrix4& rhs);
		bool operator != (const Matrix4& lhs, const Matrix4& rhs);

		std::istream& operator >> (std::istream& stream, Matrix4& matrix);
		std::istream& operator >>= (std::istream& stream, Matrix4& matrix);

		std::ostream& operator << (std::ostream& stream, const Matrix4& matrix);
		std::ostream& operator <<= (std::ostream& stream, const Matrix4& matrix);

#pragma endregion
	}
}

#endif // !ENGINEQ_MATH_MATRIX4_HPP
