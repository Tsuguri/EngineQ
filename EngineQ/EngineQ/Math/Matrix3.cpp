#include "Matrix3.hpp"

namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		Matrix3::Matrix3() :
			m00{ static_cast<Real>(0) }, m01{ static_cast<Real>(0) }, m02{ static_cast<Real>(0) },
			m10{ static_cast<Real>(0) }, m11{ static_cast<Real>(0) }, m12{ static_cast<Real>(0) },
			m20{ static_cast<Real>(0) }, m21{ static_cast<Real>(0) }, m22{ static_cast<Real>(0) }
		{
		}

		Matrix3::Matrix3(Real value) :
			m00{ value }, m01{ value }, m02{ value },
			m10{ value }, m11{ value }, m12{ value },
			m20{ value }, m21{ value }, m22{ value }
		{
		}

		Matrix3::Matrix3(
			Real m00, Real m01, Real m02,
			Real m10, Real m11, Real m12,
			Real m20, Real m21, Real m22) :
			m00{ m00 }, m01{ m01 }, m02{ m02 },
			m10{ m10 }, m11{ m11 }, m12{ m12 },
			m20{ m20 }, m21{ m21 }, m22{ m22 }
		{
		}

		Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2) :
			m00{ row0.X }, m01{ row0.Y }, m02{ row0.Z },
			m10{ row1.X }, m11{ row1.Y }, m12{ row1.Z },
			m20{ row2.X }, m21{ row2.Y }, m22{ row2.Z }
		{
		}

	#pragma endregion

	#pragma region Methods

		void Matrix3::Transpose()
		{
			Real tmp;
			tmp = m01; m01 = m10; m10 = tmp;
			tmp = m02; m02 = m20; m20 = tmp;
			tmp = m12; m12 = m21; m21 = tmp;
		}

		void Matrix3::Inverse()
		{
			*this = GetInversed();
		}

		std::string Matrix3::ToString() const
		{
			return Utilities::ToString(*this);
		}
		
		Matrix3 Matrix3::GetTransposed() const
		{
			return Matrix3{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
		}

		Matrix3 Matrix3::GetInversed() const
		{
			Real tmp1 = m11 * m22 - m12 * m21;
			Real tmp2 = m12 * m20 - m10 * m22;
			Real tmp3 = m10 * m21 - m11 * m20;

			Real det = m00 * tmp1 + m01 * tmp2 + m02 * tmp3;
			
			if (det == static_cast<Real>(0))
				return Matrix3{};
			
			Real invdet = static_cast<Real>(1) / det;

			return Matrix3{
				tmp1 * invdet, (m02 * m21 - m01 * m22) * invdet, (m01 * m12 - m02 * m11) * invdet,
				tmp2 * invdet, (m00 * m22 - m02 * m20) * invdet, (m02 * m10 - m00 * m12) * invdet,
				tmp3 * invdet, (m01 * m20 - m00 * m21) * invdet, (m00 * m11 - m01 * m10) * invdet };
		}

		Real Matrix3::GetDeterminant() const
		{
			return (m00 * (m11 * m22 - m12 * m21) + m01 * (m12 * m20 - m10 * m22) + m02 * (m10 * m21 - m11 * m20));
		}

		Vector3 Matrix3::GetDiagonal() const
		{
			return Vector3{ m00, m11, m22 };
		}

		void Matrix3::SetDiagonal(const Vector3& diagonal)
		{
			m00 = diagonal.X;
			m11 = diagonal.Y;
			m22 = diagonal.Z;
		}

		Vector3 Matrix3::GetColumn(std::size_t column) const
		{
			return Vector3{ Values2[0][column], Values2[1][column], Values2[2][column] };
		}

		void Matrix3::SetColumn(std::size_t column, Vector3 value)
		{
			Values2[0][column] = value.X;
			Values2[1][column] = value.Y;
			Values2[2][column] = value.Z;
		}

		Vector3 Matrix3::GetRow(std::size_t row) const
		{
			return Vector3{ Values2[row][0], Values2[row][1], Values2[row][2] };
		}

		void Matrix3::SetRow(std::size_t row, Vector3 value)
		{
			Values2[row][0] = value.X;
			Values2[row][1] = value.Y;
			Values2[row][2] = value.Z;
		}

		void Matrix3::GetRows(Vector3& row0, Vector3& row1, Vector3& row2) const
		{
			row0.X = m00; row0.Y = m01; row0.Z = m02;
			row1.X = m10; row1.Y = m11; row1.Z = m12;
			row2.X = m20; row2.Y = m21; row2.Z = m22;
		}

		void Matrix3::GetColumns(Vector3& column0, Vector3& column1, Vector3& column2) const
		{
			column0.X = m00; column0.Y = m10; column0.Z = m20;
			column1.X = m01; column1.Y = m11; column1.Z = m21;
			column2.X = m02; column2.Y = m12; column2.Z = m22;
		}

	#pragma endregion

	#pragma region Static Methods

		Matrix3 Matrix3::GetIdentity()
		{
			return Matrix3{
				static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
		}

		Matrix3 Matrix3::CreateFromColumns(const Vector3& column0, const Vector3& column1, const Vector3& column2)
		{
			return Matrix3{
				column0.X, column1.X, column2.X,
				column0.Y, column1.Y, column2.Y,
				column0.Z, column1.Z, column2.Z 
			};
		}

		Matrix3 Matrix3::CreateFromRows(const Vector3& row0, const Vector3& row1, const Vector3& row2)
		{
			return Matrix3{
				row0.X, row0.Y, row0.Z,
				row1.X, row1.Y, row1.Z,
				row2.X, row2.Y, row2.Z 
			};
		}

	#pragma endregion

	#pragma region Operators

		void Matrix3::operator *= (const Matrix3& matrix)
		{
			*this = *this * matrix;
		}

		void Matrix3::operator *= (Real scalar)
		{
			m00 *= scalar;
			m01 *= scalar;
			m02 *= scalar;
			m10 *= scalar;
			m11 *= scalar;
			m12 *= scalar;
			m20 *= scalar;
			m21 *= scalar;
			m22 *= scalar;
		}

		void Matrix3::operator /= (Real scalar)
		{
			*this *= static_cast<Real>(1) / scalar;
		}

		Real Matrix3::operator () (std::size_t index) const
		{
			return Values[index];
		}

		Real& Matrix3::operator () (std::size_t index)
		{
			return Values[index];
		}

		Real Matrix3::operator [] (std::size_t index) const
		{
			return Values[index];
		}

		Real& Matrix3::operator [] (std::size_t index)
		{
			return Values[index];
		}

		Real Matrix3::operator () (std::size_t row, std::size_t column) const
		{
			return Values2[row][column];
		}

		Real& Matrix3::operator () (std::size_t row, std::size_t column)
		{
			return Values2[row][column];
		}

	#pragma endregion

	#pragma region Static Operators

		Matrix3 operator * (const Matrix3& lhs, const Matrix3& rhs)
		{
			return Matrix3{
				lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20,
				lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21,
				lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22,

				lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20,
				lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21,
				lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,

				lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20,
				lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21,
				lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22
			};
		}

		Vector3 operator * (const Matrix3& matrix, const Vector3& vector)
		{
			return Vector3{
				matrix.m00 * vector.X + matrix.m01 * vector.Y + matrix.m02 * vector.Z,
				matrix.m10 * vector.X + matrix.m11 * vector.Y + matrix.m12 * vector.Z,
				matrix.m20 * vector.X + matrix.m21 * vector.Y + matrix.m22 * vector.Z
			};
		}

		Matrix3 operator * (const Matrix3& matrix, Real scalar)
		{
			Matrix3 ret = matrix;
			ret *= scalar;
			return ret;
		}

		Matrix3 operator * (Real scalar, const Matrix3& matrix)
		{
			Matrix3 ret = matrix;
			ret *= scalar;
			return ret;
		}

		Matrix3 operator / (const Matrix3& matrix, Real scalar)
		{
			Matrix3 ret = matrix;
			ret *= static_cast<Real>(1) / scalar;
			return ret;
		}

		bool operator == (const Matrix3& lhs, const Matrix3& rhs)
		{
			return
				lhs.m00 == rhs.m00 &&
				lhs.m01 == rhs.m01 &&
				lhs.m02 == rhs.m02 &&
				lhs.m10 == rhs.m10 &&
				lhs.m11 == rhs.m11 &&
				lhs.m12 == rhs.m12 &&
				lhs.m20 == rhs.m20 &&
				lhs.m21 == rhs.m21 &&
				lhs.m22 == rhs.m22;
		}

		bool operator != (const Matrix3& lhs, const Matrix3& rhs)
		{
			return
				lhs.m00 != rhs.m00 ||
				lhs.m01 != rhs.m01 ||
				lhs.m02 != rhs.m02 ||
				lhs.m10 != rhs.m10 ||
				lhs.m11 != rhs.m11 ||
				lhs.m12 != rhs.m12 ||
				lhs.m20 != rhs.m20 ||
				lhs.m21 != rhs.m21 ||
				lhs.m22 != rhs.m22;
		}

		std::istream& operator >> (std::istream& stream, Matrix3& matrix)
		{
			stream.ignore(2);
			stream >> matrix.m00;
			stream.ignore(1);
			stream >> matrix.m01;
			stream.ignore(1);
			stream >> matrix.m02;
			stream.ignore(3);
			stream >> matrix.m10;
			stream.ignore(1);
			stream >> matrix.m11;
			stream.ignore(1);
			stream >> matrix.m12;
			stream.ignore(3);
			stream >> matrix.m20;
			stream.ignore(1);
			stream >> matrix.m21;
			stream.ignore(1);
			stream >> matrix.m22;
			stream.ignore(2);

			return stream;
		}

		std::istream& operator >>= (std::istream& stream, Matrix3& matrix)
		{
			return stream.read(reinterpret_cast<char*>(&matrix.Values), sizeof(matrix.Values));
		}

		std::ostream& operator << (std::ostream& stream, const Matrix3& matrix)
		{
			return stream << "[[" <<
				matrix.m00 << "," << matrix.m01 << "," << matrix.m02 << "],[" <<
				matrix.m10 << "," << matrix.m11 << "," << matrix.m12 << "],[" <<
				matrix.m20 << "," << matrix.m21 << "," << matrix.m22 << "]]";
		}

		std::ostream& operator <<= (std::ostream& stream, const Matrix3& matrix)
		{
			return stream.write(reinterpret_cast<const char*>(matrix.Values), sizeof(matrix.Values));
		}

	#pragma endregion
	}
}