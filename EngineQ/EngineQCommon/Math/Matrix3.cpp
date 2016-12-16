#include "Matrix3.hpp"

#include "Vector3.hpp"

namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		Matrix3::Matrix3(Real value) :
			M00{ value }, M01{ value }, M02{ value },
			M10{ value }, M11{ value }, M12{ value },
			M20{ value }, M21{ value }, M22{ value }
		{
		}

		Matrix3::Matrix3(
			Real m00, Real m01, Real m02,
			Real m10, Real m11, Real m12,
			Real m20, Real m21, Real m22) :
			M00{ m00 }, M01{ m01 }, M02{ m02 },
			M10{ m10 }, M11{ m11 }, M12{ m12 },
			M20{ m20 }, M21{ m21 }, M22{ m22 }
		{
		}

		Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2) :
			M00{ row0.X }, M01{ row0.Y }, M02{ row0.Z },
			M10{ row1.X }, M11{ row1.Y }, M12{ row1.Z },
			M20{ row2.X }, M21{ row2.Y }, M22{ row2.Z }
		{
		}

	#pragma endregion

	#pragma region Methods

		void Matrix3::Transpose()
		{
			Real tmp;
			tmp = M01; M01 = M10; M10 = tmp;
			tmp = M02; M02 = M20; M20 = tmp;
			tmp = M12; M12 = M21; M21 = tmp;
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
			return Matrix3{ M00, M10, M20, M01, M11, M21, M02, M12, M22 };
		}

		Matrix3 Matrix3::GetInversed() const
		{
			Real tmp1 = M11 * M22 - M12 * M21;
			Real tmp2 = M12 * M20 - M10 * M22;
			Real tmp3 = M10 * M21 - M11 * M20;

			Real det = M00 * tmp1 + M01 * tmp2 + M02 * tmp3;
			
			if (det == static_cast<Real>(0))
				return Matrix3{};
			
			Real invdet = static_cast<Real>(1) / det;

			return Matrix3{
				tmp1 * invdet, (M02 * M21 - M01 * M22) * invdet, (M01 * M12 - M02 * M11) * invdet,
				tmp2 * invdet, (M00 * M22 - M02 * M20) * invdet, (M02 * M10 - M00 * M12) * invdet,
				tmp3 * invdet, (M01 * M20 - M00 * M21) * invdet, (M00 * M11 - M01 * M10) * invdet };
		}

		Real Matrix3::GetDeterminant() const
		{
			return (M00 * (M11 * M22 - M12 * M21) + M01 * (M12 * M20 - M10 * M22) + M02 * (M10 * M21 - M11 * M20));
		}

		Vector3 Matrix3::GetDiagonal() const
		{
			return Vector3{ M00, M11, M22 };
		}

		void Matrix3::SetDiagonal(const Vector3& diagonal)
		{
			M00 = diagonal.X;
			M11 = diagonal.Y;
			M22 = diagonal.Z;
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
			row0.X = M00; row0.Y = M01; row0.Z = M02;
			row1.X = M10; row1.Y = M11; row1.Z = M12;
			row2.X = M20; row2.Y = M21; row2.Z = M22;
		}

		void Matrix3::GetColumns(Vector3& column0, Vector3& column1, Vector3& column2) const
		{
			column0.X = M00; column0.Y = M10; column0.Z = M20;
			column1.X = M01; column1.Y = M11; column1.Z = M21;
			column2.X = M02; column2.Y = M12; column2.Z = M22;
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
			M00 *= scalar;
			M01 *= scalar;
			M02 *= scalar;
			M10 *= scalar;
			M11 *= scalar;
			M12 *= scalar;
			M20 *= scalar;
			M21 *= scalar;
			M22 *= scalar;
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
				lhs.M00 * rhs.M00 + lhs.M01 * rhs.M10 + lhs.M02 * rhs.M20,
				lhs.M00 * rhs.M01 + lhs.M01 * rhs.M11 + lhs.M02 * rhs.M21,
				lhs.M00 * rhs.M02 + lhs.M01 * rhs.M12 + lhs.M02 * rhs.M22,

				lhs.M10 * rhs.M00 + lhs.M11 * rhs.M10 + lhs.M12 * rhs.M20,
				lhs.M10 * rhs.M01 + lhs.M11 * rhs.M11 + lhs.M12 * rhs.M21,
				lhs.M10 * rhs.M02 + lhs.M11 * rhs.M12 + lhs.M12 * rhs.M22,

				lhs.M20 * rhs.M00 + lhs.M21 * rhs.M10 + lhs.M22 * rhs.M20,
				lhs.M20 * rhs.M01 + lhs.M21 * rhs.M11 + lhs.M22 * rhs.M21,
				lhs.M20 * rhs.M02 + lhs.M21 * rhs.M12 + lhs.M22 * rhs.M22
			};
		}

		Vector3 operator * (const Matrix3& matrix, const Vector3& vector)
		{
			return Vector3{
				matrix.M00 * vector.X + matrix.M01 * vector.Y + matrix.M02 * vector.Z,
				matrix.M10 * vector.X + matrix.M11 * vector.Y + matrix.M12 * vector.Z,
				matrix.M20 * vector.X + matrix.M21 * vector.Y + matrix.M22 * vector.Z
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
		//	return
		//		lhs.M00 == rhs.M00 && lhs.M01 == rhs.M01 && lhs.M02 == rhs.M02 &&
		//		lhs.M10 == rhs.M10 && lhs.M11 == rhs.M11 && lhs.M12 == rhs.M12 &&
		//		lhs.M20 == rhs.M20 && lhs.M21 == rhs.M21 && lhs.M22 == rhs.M22;
			return
				Utils::EpsEqual(lhs.M00, rhs.M00) && Utils::EpsEqual(lhs.M01, rhs.M01) && Utils::EpsEqual(lhs.M02, rhs.M02) &&
				Utils::EpsEqual(lhs.M10, rhs.M10) && Utils::EpsEqual(lhs.M11, rhs.M11) && Utils::EpsEqual(lhs.M12, rhs.M12) &&
				Utils::EpsEqual(lhs.M20, rhs.M20) && Utils::EpsEqual(lhs.M21, rhs.M21) && Utils::EpsEqual(lhs.M22, rhs.M22);
		}

		bool operator != (const Matrix3& lhs, const Matrix3& rhs)
		{
		//	return
		//		lhs.M00 != rhs.M00 || lhs.M01 != rhs.M01 || lhs.M02 != rhs.M02 ||
		//		lhs.M10 != rhs.M10 || lhs.M11 != rhs.M11 || lhs.M12 != rhs.M12 ||
		//		lhs.M20 != rhs.M20 || lhs.M21 != rhs.M21 || lhs.M22 != rhs.M22;
			return
				Utils::EpsNotEqual(lhs.M00, rhs.M00) || Utils::EpsNotEqual(lhs.M01, rhs.M01) || Utils::EpsNotEqual(lhs.M02, rhs.M02) ||
				Utils::EpsNotEqual(lhs.M10, rhs.M10) || Utils::EpsNotEqual(lhs.M11, rhs.M11) || Utils::EpsNotEqual(lhs.M12, rhs.M12) ||
				Utils::EpsNotEqual(lhs.M20, rhs.M20) || Utils::EpsNotEqual(lhs.M21, rhs.M21) || Utils::EpsNotEqual(lhs.M22, rhs.M22);
		}

		std::istream& operator >> (std::istream& stream, Matrix3& matrix)
		{
			stream.ignore(2);
			stream >> matrix.M00;
			stream.ignore(1);
			stream >> matrix.M01;
			stream.ignore(1);
			stream >> matrix.M02;
			stream.ignore(3);
			stream >> matrix.M10;
			stream.ignore(1);
			stream >> matrix.M11;
			stream.ignore(1);
			stream >> matrix.M12;
			stream.ignore(3);
			stream >> matrix.M20;
			stream.ignore(1);
			stream >> matrix.M21;
			stream.ignore(1);
			stream >> matrix.M22;
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
				matrix.M00 << "," << matrix.M01 << "," << matrix.M02 << "],[" <<
				matrix.M10 << "," << matrix.M11 << "," << matrix.M12 << "],[" <<
				matrix.M20 << "," << matrix.M21 << "," << matrix.M22 << "]]";
		}

		std::ostream& operator <<= (std::ostream& stream, const Matrix3& matrix)
		{
			return stream.write(reinterpret_cast<const char*>(matrix.Values), sizeof(matrix.Values));
		}

	#pragma endregion
	}
}