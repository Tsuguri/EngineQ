#ifndef ENGINEQ_MATH_MATRIX4_HPP
#define ENGINEQ_MATH_MATRIX4_HPP

#include "../Utilities/StringHelpers.hpp"

#include "Types.hpp"

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

			explicit Matrix4() = default;
			explicit Matrix4(Real value);
			explicit Matrix4(
				Real m00, Real m01, Real m02, Real m03,
				Real m10, Real m11, Real m12, Real m13,
				Real m20, Real m21, Real m22, Real m23,
				Real m30, Real m31, Real m32, Real m33);
			explicit Matrix4(
				const Vector4& row0,
				const Vector4& row1,
				const Vector4& row2,
				const Vector4& row3);

		#pragma endregion

		#pragma region Methods

			void Transpose();
			void Inverse();

			std::string ToString() const;

			Real GetDeterminant() const;
			Matrix4 GetTransposed() const;
			Matrix4 GetInversed() const;

			Vector4 GetDiagonal() const;
			void SetDiagonal(const Vector4& diagonal);

			Vector4 GetColumn(std::size_t column) const;
			void SetColumn(std::size_t column, const Vector4& value);

			Vector4 GetRow(std::size_t row) const;
			void SetRow(std::size_t row, const Vector4& value);

			void GetRows(Vector4& row0, Vector4& row1, Vector4& row2, Vector4& row3) const;
			void GetColumns(Vector4& column0, Vector4& column1, Vector4& column2, Vector4& column3) const;

		#pragma endregion

		#pragma region Static Methods

			static Matrix4 GetIdentity();
			static Matrix4 CreateFromRows(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
			static Matrix4 CreateFromColumns(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);
			static Matrix4 CreateRotation(const Quaternion& q);
			static Matrix4 CreateTranslation(Real x, Real y, Real z);
			static Matrix4 CreateTranslation(const Vector3& translation);
			static Matrix4 CreateScale(Real x, Real y, Real z);
			static Matrix4 CreateScale(const Vector3& scale);
			static Matrix4 CreateRotationX(Real angle);
			static Matrix4 CreateRotationY(Real angle);
			static Matrix4 CreateRotationZ(Real angle);
			static Matrix4 CreateViewport(Real x, Real y, Real width, Real height);
			static Matrix4 CreateFrustum(Real fovy, Real aspect, Real near, Real far);
			static Matrix4 CreateLookAt(const Vector3&  cameraPosition, const Vector3&  cameraTarget, const Vector3&  upVector);

			static Vector3 TransformVector(const Matrix4& matrix, const Vector3& vector);
			static Vector3 TransformPosition(const Matrix4& matrix, const Vector3& position);
			static Vector3 TransformNormal(const Matrix4& matrix, const Vector3& normal);
			static Vector3 TransformPerspective(const Matrix4& matrix, const Vector3& vector);

		#pragma endregion

		#pragma region Operators

			explicit operator Matrix3() const;

			void operator += (const Matrix4& matrix);
			void operator -= (const Matrix4& matrix);
			void operator *= (Real scalar);
			void operator /= (Real scalar);
			void operator *= (const Matrix4& matrix);

			Real operator () (std::size_t index) const;
			Real& operator () (std::size_t index);
			Real operator [] (std::size_t index) const;
			Real& operator [] (std::size_t index);
			Real operator () (std::size_t row, std::size_t column) const;
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
