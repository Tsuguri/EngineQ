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

			explicit Matrix3() = default;
			explicit Matrix3(Real value);
			explicit Matrix3(
				Real m00, Real m01, Real m02,
				Real m10, Real m11, Real m12,
				Real m20, Real m21, Real m22);
			explicit Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		#pragma endregion

		#pragma region Methods

			void Transpose();
			void Inverse();
			std::string ToString() const;
			Matrix3 GetTransposed() const;
			Matrix3 GetInversed() const;
			Real GetDeterminant() const;
			Vector3 GetDiagonal() const;
			void SetDiagonal(const Vector3& diagonal);
			Vector3 GetColumn(std::size_t column) const;
			void SetColumn(std::size_t column, Vector3 value);
			Vector3 GetRow(std::size_t row) const;
			void SetRow(std::size_t row, Vector3 value);
			void GetRows(Vector3& row0, Vector3& row1, Vector3& row2) const;
			void GetColumns(Vector3& column0, Vector3& column1, Vector3& column2) const;

		#pragma endregion

		#pragma region Static Methods

			static Matrix3 GetIdentity();
			static Matrix3 CreateFromColumns(const Vector3& column0, const Vector3& column1, const Vector3& column2);
			static Matrix3 CreateFromRows(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		#pragma endregion

		#pragma region Operators

			void operator *= (const Matrix3& matrix);
			void operator *= (Real scalar);
			void operator /= (Real scalar);

			Real operator () (std::size_t index) const;
			Real& operator () (std::size_t index);
			Real operator [] (std::size_t index) const;
			Real& operator [] (std::size_t index);
			Real operator () (std::size_t row, std::size_t column) const;
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
