#ifndef ENGINEQ_MATH_MATRIX3_HPP
#define ENGINEQ_MATH_MATRIX3_HPP

// Standard includes
#include <iostream>

// This project
#include "Types.hpp"
#include "EngineQCommon/Utilities/StringHelpers.hpp"


namespace EngineQ
{
	namespace Math
	{
		struct Matrix3
		{
		#pragma region Fields

			union
			{
				Real Values[9] = { static_cast<Real>(0) };
				Real Values2[3][3];
				struct
				{
					Real M00, M01, M02;
					Real M10, M11, M12;
					Real M20, M21, M22;
				};
			};

		#pragma endregion

		#pragma region Constructors

			/// <sumary>
			/// Constructs empty Matrix filled with zeros.
			/// </sumary>
			explicit Matrix3() = default;

			/// <sumary>
			/// Constructs Matrix filled with specified value.
			/// </sumary>
			/// <param name="value">Value to set all elements.</param>
			explicit Matrix3(Real value);

			/// <summary>
			/// Constructs Matrix from individual elements.
			/// </summary>
			/// <param name="m00">Element at row 0, column 0.</param>
			/// <param name="m01">Element at row 0, column 1.</param>
			/// <param name="m02">Element at row 0, column 2.</param>
			/// <param name="m10">Element at row 1, column 0.</param>
			/// <param name="m11">Element at row 1, column 1.</param>
			/// <param name="m12">Element at row 1, column 2.</param>
			/// <param name="m20">Element at row 2, column 0.</param>
			/// <param name="m21">Element at row 2, column 1.</param>
			/// <param name="m22">Element at row 2, column 2.</param>
			explicit Matrix3(
				Real m00, Real m01, Real m02,
				Real m10, Real m11, Real m12,
				Real m20, Real m21, Real m22);

			/// <summary>
			/// Constructs Matrix from rows.
			/// </summary>
			/// <param name="row0">Vector of elements for row 0.</param>
			/// <param name="row1">Vector of elements for row 1.</param>
			/// <param name="row2">Vector of elements for row 2.</param>
			explicit Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		#pragma endregion

		#pragma region Methods

			/// <summary>
			/// Modifies this <see cref="Matrix3"/> by transposition.
			/// </summary>
			void Transpose();

			/// <summary>
			/// Modifies this <see cref="Matrix3"/> by inversion.
			/// </summary>
			void Inverse();

			/// <summary>
			/// Returns string representation of this <see cref="Matrix3"/>. 
			/// </summary>
			/// <returns>String representation of Matrix.</returns>
			std::string ToString() const;

			/// <summary>
			/// Returns new <see cref="Matrix3"/> that is transposition of this one.
			/// </summary>
			/// <returns><see cref="Matrix3"/> that is transposition of this one.</returns>
			Matrix3 GetTransposed() const;

			/// <summary>
			/// Returns new <see cref="Matrix3"/> that is inversion of this one.
			/// </summary>
			/// <returns> <see cref="Matrix3"/> that is inversion of this one.</returns>
			Matrix3 GetInversed() const;

			/// <summary>
			/// Computes and returns determinant of this <see cref="Matrix3"/>.
			/// </summary>
			/// <returns>Determinant of this <see cref="Matrix3"/>.</returns>
			Real GetDeterminant() const;

			/// <summary>
			/// Returns <see cref="Vector3"/> of values lying on the diagonal of this <see cref="Matrix3"/>.
			/// </summary>
			/// <returns><see cref="Vector3"/> of values lying on the diagonal of this <see cref="Matrix3"/>.</returns>
			Vector3 GetDiagonal() const;

			/// <summary>
			/// Sets values lying on the diagonal of this <see cref="Matrix3"/>.
			/// </summary>
			/// <param name="diagonal"><see cref="Vector3"/> of elements to set as diagonal.</param>
			void SetDiagonal(const Vector3& diagonal);

			/// <summary>
			/// <see cref="Vector3"/> representing one of columns of this <see cref="Matrix3"/>.
			/// </summary>
			/// <param name="column">Index of column.</param>
			/// <returns><see cref="Vector3"/> representing column.</returns>
			Vector3 GetColumn(std::size_t column) const;

			/// <summary>
			/// Sets content of <paramref name="column"/> with given <see cref="Vector3"/> <paramref name="value"/>.
			/// </summary>
			/// <param name="column">Index of column to set.</param>
			/// <param name="value">New values.</param>
			void SetColumn(std::size_t column, Vector3 value);

			/// <summary>
			/// <see cref="Vector3"/> representing one of rows of this <see cref="Matrix3"/>.
			/// </summary>
			/// <param name="row">Index of row.</param>
			/// <returns><see cref="Vector3"/> representing row.</returns>
			Vector3 GetRow(std::size_t row) const;

			/// <summary>
			/// Sets content fo <paramref name="row"/>  with given <see cref="Vector3"/> <paramref name="value"/>.
			/// </summary>
			/// <param name="row">Index of the row to set.</param>
			/// <param name="value"><see cref="Vector3"/> of values to set in the row.</param>
			void SetRow(std::size_t row, Vector3 value);

			/// <summary>
			/// Extracts this <see cref="Matrix3"/>'s rows into given <see cref="Vector3"/>s references. 
			/// </summary>
			/// <param name="row0">Reference to the <see cref="Vector3"/> that will contain values from first row.</param>
			/// <param name="row1">Reference to the <see cref="Vector3"/> that will contain values from second row.</param>
			/// <param name="row2">Reference to the <see cref="Vector3"/> that will contain values from third row.</param>
			void GetRows(Vector3& row0, Vector3& row1, Vector3& row2) const;
			
			/// <summary>
			/// Extracts this <see cref="Matrix3"/>'s columns into given <see cref="Vector3"/>s references. 
			/// </summary>
			/// <param name="row0">Reference to the <see cref="Vector3"/> that will contain values from first column.</param>
			/// <param name="row1">Reference to the <see cref="Vector3"/> that will contain values from second column.</param>
			/// <param name="row2">Reference to the <see cref="Vector3"/> that will contain values from third column.</param>
			void GetColumns(Vector3& column0, Vector3& column1, Vector3& column2) const;

		#pragma endregion

		#pragma region Static Methods

			/// <summary>
			/// Returns identity Matrix
			/// </summary>
			/// <returns>Identity Matrix</returns>
			static Matrix3 GetIdentity();
			
			/// <summary>
			/// Creates <see cref="Matrix3"/> from given <see cref="Vector3"/>s representing columns.
			/// </summary>
			/// <param name="column0">First column.</param>
			/// <param name="column1">Second column.</param>
			/// <param name="column2">Third column.</param>
			/// <returns><see cref="Matrix3"/> created from given rows.</returns>
			static Matrix3 CreateFromColumns(const Vector3& column0, const Vector3& column1, const Vector3& column2);
			
			/// <summary>
			/// Creates <see cref="Matrix3"/> from given <see cref="Vector3"/>s representing rows.
			/// </summary>
			/// <param name="row0">First row.</param>
			/// <param name="row1">Second row.</param>
			/// <param name="row2">Third row.</param>
			/// <returns><see cref="Matrix3"/> created from given columns.</returns>
			static Matrix3 CreateFromRows(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		#pragma endregion

		#pragma region Operators

			void operator *= (const Matrix3& matrix);
			void operator *= (Real scalar);
			void operator /= (Real scalar);

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

		Matrix3 operator * (const Matrix3& lhs, const Matrix3& rhs);
		Vector3 operator * (const Matrix3& matrix, const Vector3& vector);
		Matrix3 operator * (const Matrix3& matrix, Real scalar);
		Matrix3 operator * (Real scalar, const Matrix3& matrix);
		Matrix3 operator / (const Matrix3& matrix, Real scalar);

		bool operator == (const Matrix3& lhs, const Matrix3& rhs);
		bool operator != (const Matrix3& lhs, const Matrix3& rhs);

		std::istream& operator >> (std::istream& stream, Matrix3& matrix);
		std::istream& operator >>= (std::istream& stream, Matrix3& matrix);

		std::ostream& operator << (std::ostream& stream, const Matrix3& matrix);
		std::ostream& operator <<= (std::ostream& stream, const Matrix3& matrix);

	#pragma endregion
	}
}

#endif // !ENGINEQ_MATH_MATRIX3_HPP
