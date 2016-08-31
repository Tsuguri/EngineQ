#include "Matrix4.hpp"

namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		Matrix4::Matrix4() :
			m00{ static_cast<Real>(0) }, m01{ static_cast<Real>(0) }, m02{ static_cast<Real>(0) }, m03{ static_cast<Real>(0) },
			m10{ static_cast<Real>(0) }, m11{ static_cast<Real>(0) }, m12{ static_cast<Real>(0) }, m13{ static_cast<Real>(0) },
			m20{ static_cast<Real>(0) }, m21{ static_cast<Real>(0) }, m22{ static_cast<Real>(0) }, m23{ static_cast<Real>(0) },
			m30{ static_cast<Real>(0) }, m31{ static_cast<Real>(0) }, m32{ static_cast<Real>(0) }, m33{ static_cast<Real>(0) }
		{
		}

		Matrix4::Matrix4(Real value) :
			m00{ value }, m01{ value }, m02{ value }, m03{ value },
			m10{ value }, m11{ value }, m12{ value }, m13{ value },
			m20{ value }, m21{ value }, m22{ value }, m23{ value },
			m30{ value }, m31{ value }, m32{ value }, m33{ value }
		{
		}

		Matrix4::Matrix4(
			Real m00, Real m01, Real m02, Real m03,
			Real m10, Real m11, Real m12, Real m13,
			Real m20, Real m21, Real m22, Real m23,
			Real m30, Real m31, Real m32, Real m33) :
			m00{ m00 }, m01{ m01 }, m02{ m02 }, m03{ m03 },
			m10{ m10 }, m11{ m11 }, m12{ m12 }, m13{ m13 },
			m20{ m20 }, m21{ m21 }, m22{ m22 }, m23{ m23 },
			m30{ m30 }, m31{ m31 }, m32{ m32 }, m33{ m33 }
		{
		}

		Matrix4::Matrix4(
			const Vector4& row0,
			const Vector4& row1,
			const Vector4& row2,
			const Vector4& row3) :
			m00{ row0.X }, m01{ row0.Y }, m02{ row0.Z }, m03{ row0.W },
			m10{ row1.X }, m11{ row1.Y }, m12{ row1.Z }, m13{ row1.W },
			m20{ row2.X }, m21{ row2.Y }, m22{ row2.Z }, m23{ row2.W },
			m30{ row3.X }, m31{ row3.Y }, m32{ row3.Z }, m33{ row3.W }
		{
		}

	#pragma endregion

	#pragma region Methods

		void Matrix4::Transpose()
		{
			Real tmp;
			tmp = m01; m01 = m10; m10 = tmp;
			tmp = m02; m02 = m20; m20 = tmp;
			tmp = m03; m03 = m30; m30 = tmp;
			tmp = m12; m12 = m21; m21 = tmp;
			tmp = m13; m13 = m31; m31 = tmp;
			tmp = m23; m23 = m32; m32 = tmp;
		}

		void Matrix4::Inverse()
		{
			*this = GetInversed();
		}

		std::string Matrix4::ToString() const
		{
			return Utilities::ToString(*this);
		}

		Real Matrix4::GetDeterminant() const
		{
			Real tmp1 =
				m11 * m22 * m33 -
				m11 * m23 * m32 -
				m21 * m12 * m33 +
				m21 * m13 * m32 +
				m31 * m12 * m23 -
				m31 * m13 * m22;

			Real tmp2 =
				-m10 * m22 * m33 +
				m10 * m23 * m32 +
				m20 * m12 * m33 -
				m20 * m13 * m32 -
				m30 * m12 * m23 +
				m30 * m13 * m22;

			Real tmp3 =
				m10 * m21 * m33 -
				m10 * m23 * m31 -
				m20 * m11 * m33 +
				m20 * m13 * m31 +
				m30 * m11 * m23 -
				m30 * m13 * m21;

			Real tmp4 =
				-m10 * m21 * m32 +
				m10 * m22 * m31 +
				m20 * m11 * m32 -
				m20 * m12 * m31 -
				m30 * m11 * m22 +
				m30 * m12 * m21;

			return m00 * tmp1 + m01 * tmp2 + m02 * tmp3 + m03 * tmp4;
		}

		Matrix4 Matrix4::GetTransposed() const
		{
			return Matrix4{
				m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33 };
		}

		Matrix4 Matrix4::GetInversed() const
		{
			Real tmp1 =
				m11 * m22 * m33 -
				m11 * m23 * m32 -
				m21 * m12 * m33 +
				m21 * m13 * m32 +
				m31 * m12 * m23 -
				m31 * m13 * m22;

			Real tmp2 =
				-m10 * m22 * m33 +
				m10 * m23 * m32 +
				m20 * m12 * m33 -
				m20 * m13 * m32 -
				m30 * m12 * m23 +
				m30 * m13 * m22;

			Real tmp3 =
				m10 * m21 * m33 -
				m10 * m23 * m31 -
				m20 * m11 * m33 +
				m20 * m13 * m31 +
				m30 * m11 * m23 -
				m30 * m13 * m21;

			Real tmp4 =
				-m10 * m21 * m32 +
				m10 * m22 * m31 +
				m20 * m11 * m32 -
				m20 * m12 * m31 -
				m30 * m11 * m22 +
				m30 * m12 * m21;

			Real det = m00 * tmp1 + m01 * tmp2 + m02 * tmp3 + m03 * tmp4;

			if (det == static_cast<Real>(0))
				return Matrix4{};

			Real invdet = static_cast<Real>(1) / det;

			return Matrix4{
				tmp1 * invdet,

				(-m01 * m22 * m33 +
				m01 * m23 * m32 +
				m21 * m02 * m33 -
				m21 * m03 * m32 -
				m31 * m02 * m23 +
				m31 * m03 * m22) * invdet,

				(m01 * m12 * m33 -
				m01 * m13 * m32 -
				m11 * m02 * m33 +
				m11 * m03 * m32 +
				m31 * m02 * m13 -
				m31 * m03 * m12) * invdet,

				(-m01 * m12 * m23 +
				m01 * m13 * m22 +
				m11 * m02 * m23 -
				m11 * m03 * m22 -
				m21 * m02 * m13 +
				m21 * m03 * m12) * invdet,

				tmp2 * invdet,

				(m00 * m22 * m33 -
				m00 * m23 * m32 -
				m20 * m02 * m33 +
				m20 * m03 * m32 +
				m30 * m02 * m23 -
				m30 * m03 * m22) * invdet,

				(-m00 * m12 * m33 +
				m00 * m13 * m32 +
				m10 * m02 * m33 -
				m10 * m03 * m32 -
				m30 * m02 * m13 +
				m30 * m03 * m12) * invdet,

				(m00 * m12 * m23 -
				m00 * m13 * m22 -
				m10 * m02 * m23 +
				m10 * m03 * m22 +
				m20 * m02 * m13 -
				m20 * m03 * m12) * invdet,

				tmp3 * invdet,

				(-m00 * m21 * m33 +
				m00 * m23 * m31 +
				m20 * m01 * m33 -
				m20 * m03 * m31 -
				m30 * m01 * m23 +
				m30 * m03 * m21) * invdet,

				(m00 * m11 * m33 -
				m00 * m13 * m31 -
				m10 * m01 * m33 +
				m10 * m03 * m31 +
				m30 * m01 * m13 -
				m30 * m03 * m11) * invdet,

				(-m00 * m11 * m23 +
				m00 * m13 * m21 +
				m10 * m01 * m23 -
				m10 * m03 * m21 -
				m20 * m01 * m13 +
				m20 * m03 * m11) * invdet,

				tmp4 * invdet,

				(m00 * m21 * m32 -
				m00 * m22 * m31 -
				m20 * m01 * m32 +
				m20 * m02 * m31 +
				m30 * m01 * m22 -
				m30 * m02 * m21) * invdet,

				(-m00 * m11 * m32 +
				m00 * m12 * m31 +
				m10 * m01 * m32 -
				m10 * m02 * m31 -
				m30 * m01 * m12 +
				m30 * m02 * m11) * invdet,

				(m00 * m11 * m22 -
				m00 * m12 * m21 -
				m10 * m01 * m22 +
				m10 * m02 * m21 +
				m20 * m01 * m12 -
				m20 * m02 * m11) * invdet
			};
		}

		Vector4 Matrix4::GetDiagonal() const
		{
			return Vector4{ m00, m11, m22, m33 };
		}

		void Matrix4::SetDiagonal(const Vector4& diagonal)
		{
			m00 = diagonal.X;
			m11 = diagonal.Y;
			m22 = diagonal.Z;
			m33 = diagonal.W;
		}

		Vector4 Matrix4::GetColumn(std::size_t column) const
		{
			return Vector4{ Values2[0][column], Values2[1][column], Values2[2][column], Values2[3][column] };
		}

		void Matrix4::SetColumn(std::size_t column, const Vector4& value)
		{
			Values2[0][column] = value.X;
			Values2[1][column] = value.Y;
			Values2[2][column] = value.Z;
			Values2[3][column] = value.W;
		}

		Vector4 Matrix4::GetRow(std::size_t row) const
		{
			return Vector4{ Values2[row][0], Values2[row][1], Values2[row][2], Values2[row][3] };
		}

		void Matrix4::SetRow(std::size_t row, const Vector4& value)
		{
			Values2[row][0] = value.X;
			Values2[row][1] = value.Y;
			Values2[row][2] = value.Z;
			Values2[row][3] = value.W;
		}

		void Matrix4::GetRows(Vector4& row0, Vector4& row1, Vector4& row2, Vector4& row3) const
		{
			row0.X = m00; row0.Y = m01; row0.Z = m02; row0.W = m03;
			row1.X = m10; row1.Y = m11; row1.Z = m12; row1.W = m13;
			row2.X = m20; row2.Y = m21; row2.Z = m22; row2.W = m23;
			row3.X = m30; row3.Y = m31; row3.Z = m32; row3.W = m33;
		}

		void Matrix4::GetColumns(Vector4& column0, Vector4& column1, Vector4& column2, Vector4& column3) const
		{
			column0.X = m00; column0.Y = m10; column0.Z = m20; column0.W = m30;
			column1.X = m01; column1.Y = m11; column1.Z = m21; column1.W = m31;
			column2.X = m02; column2.Y = m12; column2.Z = m22; column2.W = m32;
			column3.X = m03; column3.Y = m13; column3.Z = m23; column3.W = m33;
		}

	#pragma endregion

	#pragma region Static Methods

		Matrix4 Matrix4::GetIdentity()
		{
			return Matrix4{
				static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateFromRows(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
		{
			return Matrix4{
				row0.X, row0.Y, row0.Z, row0.W,
				row1.X, row1.Y, row1.Z, row1.W,
				row2.X, row2.Y, row2.Z, row2.W,
				row3.X, row3.Y, row3.Z, row3.W
			};
		}

		Matrix4 Matrix4::CreateFromColumns(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3)
		{
			return Matrix4{
				column0.X, column1.X, column2.X, column3.X,
				column0.Y, column1.Y, column2.Y, column3.Y,
				column0.Z, column1.Z, column2.Z, column3.Z,
				column0.W, column1.W, column2.W, column3.W
			};
		}

		Matrix4 Matrix4::CreateRotation(const Quaternion& q)
		{
			Real x2 = q.X * static_cast<Real>(2);
			Real y2 = q.Y * static_cast<Real>(2);
			Real z2 = q.Z * static_cast<Real>(2);
			Real xx = q.X * x2;
			Real yy = q.Y * y2;
			Real zz = q.Z * z2;
			Real xy = q.X * y2;
			Real xz = q.X * z2;
			Real yz = q.Y * z2;
			Real wx = q.W * x2;
			Real wy = q.W * y2;
			Real wz = q.W * z2;

			return Matrix4{
				static_cast<Real>(1) - (yy + zz), xy - wz, xz + wy, static_cast<Real>(0),
				xy + wz, static_cast<Real>(1) - (xx + zz), yz - wx, static_cast<Real>(0),
				xz - wy, yz + wx, static_cast<Real>(1) - (xx + yy), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateTranslation(Real x, Real y, Real z)
		{
			return Matrix4{
				static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), x,
				static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), y,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), z,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateTranslation(const Vector3& translation)
		{
			return Matrix4{
				static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), translation.X,
				static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), translation.Y,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), translation.Z,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateScale(Real x, Real y, Real z)
		{
			return Matrix4{
				x, static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0),       y, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0),       z, static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateScale(const Vector3& scale)
		{
			return Matrix4{
				scale.X, static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), scale.Y, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), scale.Z, static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateRotationX(Real angle)
		{
			Real s = std::sin(angle);
			Real c = std::cos(angle);

			return Matrix4{
				static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0),       c,      -s, static_cast<Real>(0),
				static_cast<Real>(0),	   s,       c, static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateRotationY(Real angle)
		{
			Real s = std::sin(angle);
			Real c = std::cos(angle);

			return Matrix4{
				      c, static_cast<Real>(0),       s, static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0),
				-s,      static_cast<Real>(0),       c, static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateRotationZ(Real angle)
		{
			Real s = std::sin(angle);
			Real c = std::cos(angle);

			return Matrix4{
				      c,      -s, static_cast<Real>(0), static_cast<Real>(0),
				      s,       c, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateViewport(Real x, Real y, Real width, Real height)
		{
			return Matrix4{
				 width,  static_cast<Real>(0), static_cast<Real>(0),       x,
				static_cast<Real>(0),  height, static_cast<Real>(0),       y,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateFrustum(Real fovy, Real aspect, Real near, Real far)
		{
			Real cot = static_cast<Real>(1) / std::tan(fovy / static_cast<Real>(2));
			Real diff = static_cast<Real>(1) / (far - near);

			return Matrix4{
				cot / aspect, static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), cot, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), -(far + near) * diff, static_cast<Real>(2) * far * near * diff,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0)
			};
		}

		Matrix4 Matrix4::CreateLookAt(const Vector3& cameraPosition, const Vector3&  cameraTarget, const Vector3&  upVector)
		{
			Vector3 zaxis = (cameraTarget - cameraPosition).GetNormalized();
			Vector3 xaxis = Vector3::CrossProduct(upVector, zaxis).GetNormalized();
			Vector3 yaxis = Vector3::CrossProduct(zaxis, xaxis);

			return Matrix4{
				xaxis.X, xaxis.Y, xaxis.Z, -Vector3::DotProduct(xaxis, cameraPosition),
				yaxis.X, yaxis.Y, yaxis.Z, -Vector3::DotProduct(yaxis, cameraPosition),
				zaxis.X, zaxis.Y, zaxis.Z, -Vector3::DotProduct(zaxis, cameraPosition),
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};

			//return Matrix4{
			//	xaxis.X, yaxis.X, zaxis.X, 0,
			//	xaxis.Y, yaxis.Y, zaxis.Y, 0,
			//	xaxis.Z, yaxis.Z, zaxis.Z, 0,
			//	-Vector3::DotProduct(xaxis, cameraPosition), -Vector3::DotProduct(yaxis, cameraPosition), -Vector3::DotProduct(zaxis, cameraPosition), 1
			//};
		}

		Vector3 Matrix4::TransformVector(const Matrix4& matrix, const Vector3& vector)
		{
			return Vector3{
				matrix.m00 * vector.X + matrix.m01 * vector.Y + matrix.m02 * vector.Z,
				matrix.m10 * vector.X + matrix.m11 * vector.Y + matrix.m12 * vector.Z,
				matrix.m20 * vector.X + matrix.m21 * vector.Y + matrix.m22 * vector.Z
			};
		}

		Vector3 Matrix4::TransformPosition(const Matrix4& matrix, const Vector3& position)
		{
			return Vector3{
				matrix.m00 * position.X + matrix.m01 * position.Y + matrix.m02 * position.Z + matrix.m03,
				matrix.m10 * position.X + matrix.m11 * position.Y + matrix.m12 * position.Z + matrix.m13,
				matrix.m20 * position.X + matrix.m21 * position.Y + matrix.m22 * position.Z + matrix.m23
			};
		}

		Vector3 Matrix4::TransformNormal(const Matrix4& matrix, const Vector3& normal)
		{
			Matrix4 matInv = matrix.GetInversed();
			return Vector3{
				matInv.m00 * normal.X + matInv.m10 * normal.Y + matInv.m20 * normal.Z,
				matInv.m01 * normal.X + matInv.m11 * normal.Y + matInv.m21 * normal.Z,
				matInv.m02 * normal.X + matInv.m12 * normal.Y + matInv.m22 * normal.Z
			};
		}

		Vector3 Matrix4::TransformPerspective(const Matrix4& matrix, const Vector3& vector)
		{
			Vector4 result = Vector4{ vector, static_cast<Real>(1) };
			result = matrix * result;
			return static_cast<Vector3>(result) / result.W;
		}

	#pragma endregion

	#pragma region Operators

		Matrix4::operator Matrix3()
		{
			return Matrix3{ m00, m01, m02, m10, m11, m12, m20, m21, m22 };
		}

		void Matrix4::operator += (const Matrix4& matrix)
		{
			m00 += matrix.m00;
			m01 += matrix.m01;
			m02 += matrix.m02;
			m03 += matrix.m03;
			m10 += matrix.m10;
			m11 += matrix.m11;
			m12 += matrix.m12;
			m13 += matrix.m13;
			m20 += matrix.m20;
			m21 += matrix.m21;
			m22 += matrix.m22;
			m23 += matrix.m23;
			m30 += matrix.m30;
			m31 += matrix.m31;
			m32 += matrix.m32;
			m33 += matrix.m33;

		}

		void Matrix4::operator -= (const Matrix4& matrix)
		{
			m00 -= matrix.m00;
			m01 -= matrix.m01;
			m02 -= matrix.m02;
			m03 -= matrix.m03;
			m10 -= matrix.m10;
			m11 -= matrix.m11;
			m12 -= matrix.m12;
			m13 -= matrix.m13;
			m20 -= matrix.m20;
			m21 -= matrix.m21;
			m22 -= matrix.m22;
			m23 -= matrix.m23;
			m30 -= matrix.m30;
			m31 -= matrix.m31;
			m32 -= matrix.m32;
			m33 -= matrix.m33;
		}

		void Matrix4::operator *= (Real scalar)
		{
			m00 *= scalar;
			m01 *= scalar;
			m02 *= scalar;
			m03 *= scalar;
			m10 *= scalar;
			m11 *= scalar;
			m12 *= scalar;
			m13 *= scalar;
			m20 *= scalar;
			m21 *= scalar;
			m22 *= scalar;
			m23 *= scalar;
			m30 *= scalar;
			m31 *= scalar;
			m32 *= scalar;
			m33 *= scalar;
		}

		void Matrix4::operator /= (Real scalar)
		{
			*this *= static_cast<Real>(1) / scalar;
		}

		void Matrix4::operator *= (const Matrix4& matrix)
		{
			*this = *this * matrix;
		}

		Real Matrix4::operator () (std::size_t index) const
		{
			return Values[index];
		}

		Real& Matrix4::operator () (std::size_t index)
		{
			return Values[index];
		}

		Real Matrix4::operator [] (std::size_t index) const
		{
			return Values[index];
		}

		Real& Matrix4::operator [] (std::size_t index)
		{
			return Values[index];
		}

		Real Matrix4::operator () (std::size_t row, std::size_t column) const
		{
			return Values2[row][column];
		}

		Real& Matrix4::operator () (std::size_t row, std::size_t column)
		{
			return Values2[row][column];
		}

	#pragma endregion

	#pragma region Static Operators

		Matrix4 operator + (const Matrix4& matrix)
		{
			return matrix;
		}

		Matrix4 operator - (const Matrix4& matrix)
		{
			return Matrix4{
				-matrix.m00, -matrix.m01, -matrix.m02, -matrix.m03,
				-matrix.m10, -matrix.m11, -matrix.m12, -matrix.m13,
				-matrix.m20, -matrix.m21, -matrix.m22, -matrix.m23,
				-matrix.m30, -matrix.m31, -matrix.m32, -matrix.m33
			};
		}

		Matrix4 operator + (const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 ret = lhs;
			ret += rhs;
			return ret;
		}

		Matrix4 operator - (const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 ret = lhs;
			ret -= rhs;
			return ret;
		}

		Matrix4 operator * (const Matrix4& matrix, Real scalar)
		{
			Matrix4 ret = matrix;
			ret *= scalar;
			return ret;
		}

		Matrix4 operator * (Real scalar, const Matrix4& matrix)
		{
			Matrix4 ret = matrix;
			ret *= scalar;
			return ret;
		}

		Vector4 operator * (const Matrix4& lhs, const Vector4& rhs)
		{
			return Vector4{
				lhs.m00 * rhs.X + lhs.m01 * rhs.Y + lhs.m02 * rhs.Z + lhs.m03 * rhs.W,
				lhs.m10 * rhs.X + lhs.m11 * rhs.Y + lhs.m12 * rhs.Z + lhs.m13 * rhs.W,
				lhs.m20 * rhs.X + lhs.m21 * rhs.Y + lhs.m22 * rhs.Z + lhs.m23 * rhs.W,
				lhs.m30 * rhs.X + lhs.m31 * rhs.Y + lhs.m32 * rhs.Z + lhs.m33 * rhs.W
			};
		}

		Matrix4 operator * (const Matrix4& lhs, const Matrix4& rhs)
		{
			return Matrix4{
				lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30,
				lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31,
				lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32,
				lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33,

				lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30,
				lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31,
				lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32,
				lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33,

				lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30,
				lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31,
				lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32,
				lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33,

				lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30,
				lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31,
				lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32,
				lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33
			};
		}

		Matrix4 operator / (const Matrix4& matrix, Real scalar)
		{
			Matrix4 ret = matrix;
			ret *= static_cast<Real>(1) / scalar;
			return ret;
		}

		std::istream& operator >> (std::istream& stream, Matrix4& matrix)
		{
			stream.ignore(2);
			stream >> matrix.m00;
			stream.ignore(1);
			stream >> matrix.m01;
			stream.ignore(1);
			stream >> matrix.m02;
			stream.ignore(1);
			stream >> matrix.m03;
			stream.ignore(3);
			stream >> matrix.m10;
			stream.ignore(1);
			stream >> matrix.m11;
			stream.ignore(1);
			stream >> matrix.m12;
			stream.ignore(1);
			stream >> matrix.m13;
			stream.ignore(3);
			stream >> matrix.m20;
			stream.ignore(1);
			stream >> matrix.m21;
			stream.ignore(1);
			stream >> matrix.m22;
			stream.ignore(1);
			stream >> matrix.m23;
			stream.ignore(3);
			stream >> matrix.m30;
			stream.ignore(1);
			stream >> matrix.m31;
			stream.ignore(1);
			stream >> matrix.m32;
			stream.ignore(1);
			stream >> matrix.m33;
			stream.ignore(2);

			return stream;
		}

		std::istream& operator >>= (std::istream& stream, Matrix4& matrix)
		{
			return stream.read(reinterpret_cast<char*>(&matrix.Values), sizeof(matrix.Values));
		}

		std::ostream& operator << (std::ostream& stream, const Matrix4& matrix)
		{
			return stream << "[[" <<
				matrix.m00 << "," << matrix.m01 << "," << matrix.m02 << "," << matrix.m03 << "],[" <<
				matrix.m10 << "," << matrix.m11 << "," << matrix.m12 << "," << matrix.m13 << "],[" <<
				matrix.m20 << "," << matrix.m21 << "," << matrix.m22 << "," << matrix.m23 << "],[" << 
				matrix.m30 << "," << matrix.m31 << "," << matrix.m32 << "," << matrix.m33 << "]]";
		}

		std::ostream& operator <<= (std::ostream& stream, const Matrix4& matrix)
		{
			return stream.write(reinterpret_cast<const char*>(matrix.Values), sizeof(matrix.Values));
		}

	#pragma endregion
	}
}