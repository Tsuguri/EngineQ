#include "Matrix4.hpp"

// This project
#include "Matrix3.hpp"
#include "Quaternion.hpp"
#include "Vector4.hpp"
#include "Utils.hpp"


namespace EngineQ
{
	namespace Math
	{
#pragma region Constructors

		Matrix4::Matrix4(Real value) :
			M00{ value }, M01{ value }, M02{ value }, M03{ value },
			M10{ value }, M11{ value }, M12{ value }, M13{ value },
			M20{ value }, M21{ value }, M22{ value }, M23{ value },
			M30{ value }, M31{ value }, M32{ value }, M33{ value }
		{
		}

		Matrix4::Matrix4(
			Real m00, Real m01, Real m02, Real m03,
			Real m10, Real m11, Real m12, Real m13,
			Real m20, Real m21, Real m22, Real m23,
			Real m30, Real m31, Real m32, Real m33) :
			M00{ m00 }, M01{ m01 }, M02{ m02 }, M03{ m03 },
			M10{ m10 }, M11{ m11 }, M12{ m12 }, M13{ m13 },
			M20{ m20 }, M21{ m21 }, M22{ m22 }, M23{ m23 },
			M30{ m30 }, M31{ m31 }, M32{ m32 }, M33{ m33 }
		{
		}

		Matrix4::Matrix4(
			const Vector4& row0,
			const Vector4& row1,
			const Vector4& row2,
			const Vector4& row3) :
			M00{ row0.X }, M01{ row0.Y }, M02{ row0.Z }, M03{ row0.W },
			M10{ row1.X }, M11{ row1.Y }, M12{ row1.Z }, M13{ row1.W },
			M20{ row2.X }, M21{ row2.Y }, M22{ row2.Z }, M23{ row2.W },
			M30{ row3.X }, M31{ row3.Y }, M32{ row3.Z }, M33{ row3.W }
		{
		}

#pragma endregion

#pragma region Methods

		void Matrix4::Transpose()
		{
			Real tmp;
			tmp = M01; M01 = M10; M10 = tmp;
			tmp = M02; M02 = M20; M20 = tmp;
			tmp = M03; M03 = M30; M30 = tmp;
			tmp = M12; M12 = M21; M21 = tmp;
			tmp = M13; M13 = M31; M31 = tmp;
			tmp = M23; M23 = M32; M32 = tmp;
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
				M11 * M22 * M33 -
				M11 * M23 * M32 -
				M21 * M12 * M33 +
				M21 * M13 * M32 +
				M31 * M12 * M23 -
				M31 * M13 * M22;

			Real tmp2 =
				-M10 * M22 * M33 +
				M10 * M23 * M32 +
				M20 * M12 * M33 -
				M20 * M13 * M32 -
				M30 * M12 * M23 +
				M30 * M13 * M22;

			Real tmp3 =
				M10 * M21 * M33 -
				M10 * M23 * M31 -
				M20 * M11 * M33 +
				M20 * M13 * M31 +
				M30 * M11 * M23 -
				M30 * M13 * M21;

			Real tmp4 =
				-M10 * M21 * M32 +
				M10 * M22 * M31 +
				M20 * M11 * M32 -
				M20 * M12 * M31 -
				M30 * M11 * M22 +
				M30 * M12 * M21;

			return M00 * tmp1 + M01 * tmp2 + M02 * tmp3 + M03 * tmp4;
		}

		Matrix4 Matrix4::GetTransposed() const
		{
			return Matrix4{
				M00, M10, M20, M30,
				M01, M11, M21, M31,
				M02, M12, M22, M32,
				M03, M13, M23, M33 };
		}

		Matrix4 Matrix4::GetInversed() const
		{
			Real tmp1 =
				M11 * M22 * M33 -
				M11 * M23 * M32 -
				M21 * M12 * M33 +
				M21 * M13 * M32 +
				M31 * M12 * M23 -
				M31 * M13 * M22;

			Real tmp2 =
				-M10 * M22 * M33 +
				M10 * M23 * M32 +
				M20 * M12 * M33 -
				M20 * M13 * M32 -
				M30 * M12 * M23 +
				M30 * M13 * M22;

			Real tmp3 =
				M10 * M21 * M33 -
				M10 * M23 * M31 -
				M20 * M11 * M33 +
				M20 * M13 * M31 +
				M30 * M11 * M23 -
				M30 * M13 * M21;

			Real tmp4 =
				-M10 * M21 * M32 +
				M10 * M22 * M31 +
				M20 * M11 * M32 -
				M20 * M12 * M31 -
				M30 * M11 * M22 +
				M30 * M12 * M21;

			Real det = M00 * tmp1 + M01 * tmp2 + M02 * tmp3 + M03 * tmp4;

			if (det == static_cast<Real>(0))
				return Matrix4{};

			Real invdet = static_cast<Real>(1) / det;

			return Matrix4{
				tmp1 * invdet,

				(-M01 * M22 * M33 +
				M01 * M23 * M32 +
				M21 * M02 * M33 -
				M21 * M03 * M32 -
				M31 * M02 * M23 +
				M31 * M03 * M22) * invdet,

				(M01 * M12 * M33 -
				M01 * M13 * M32 -
				M11 * M02 * M33 +
				M11 * M03 * M32 +
				M31 * M02 * M13 -
				M31 * M03 * M12) * invdet,

				(-M01 * M12 * M23 +
				M01 * M13 * M22 +
				M11 * M02 * M23 -
				M11 * M03 * M22 -
				M21 * M02 * M13 +
				M21 * M03 * M12) * invdet,

				tmp2 * invdet,

				(M00 * M22 * M33 -
				M00 * M23 * M32 -
				M20 * M02 * M33 +
				M20 * M03 * M32 +
				M30 * M02 * M23 -
				M30 * M03 * M22) * invdet,

				(-M00 * M12 * M33 +
				M00 * M13 * M32 +
				M10 * M02 * M33 -
				M10 * M03 * M32 -
				M30 * M02 * M13 +
				M30 * M03 * M12) * invdet,

				(M00 * M12 * M23 -
				M00 * M13 * M22 -
				M10 * M02 * M23 +
				M10 * M03 * M22 +
				M20 * M02 * M13 -
				M20 * M03 * M12) * invdet,

				tmp3 * invdet,

				(-M00 * M21 * M33 +
				M00 * M23 * M31 +
				M20 * M01 * M33 -
				M20 * M03 * M31 -
				M30 * M01 * M23 +
				M30 * M03 * M21) * invdet,

				(M00 * M11 * M33 -
				M00 * M13 * M31 -
				M10 * M01 * M33 +
				M10 * M03 * M31 +
				M30 * M01 * M13 -
				M30 * M03 * M11) * invdet,

				(-M00 * M11 * M23 +
				M00 * M13 * M21 +
				M10 * M01 * M23 -
				M10 * M03 * M21 -
				M20 * M01 * M13 +
				M20 * M03 * M11) * invdet,

				tmp4 * invdet,

				(M00 * M21 * M32 -
				M00 * M22 * M31 -
				M20 * M01 * M32 +
				M20 * M02 * M31 +
				M30 * M01 * M22 -
				M30 * M02 * M21) * invdet,

				(-M00 * M11 * M32 +
				M00 * M12 * M31 +
				M10 * M01 * M32 -
				M10 * M02 * M31 -
				M30 * M01 * M12 +
				M30 * M02 * M11) * invdet,

				(M00 * M11 * M22 -
				M00 * M12 * M21 -
				M10 * M01 * M22 +
				M10 * M02 * M21 +
				M20 * M01 * M12 -
				M20 * M02 * M11) * invdet
			};
		}

		Vector4 Matrix4::GetDiagonal() const
		{
			return Vector4{ M00, M11, M22, M33 };
		}

		void Matrix4::SetDiagonal(const Vector4& diagonal)
		{
			M00 = diagonal.X;
			M11 = diagonal.Y;
			M22 = diagonal.Z;
			M33 = diagonal.W;
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
			row0.X = M00; row0.Y = M01; row0.Z = M02; row0.W = M03;
			row1.X = M10; row1.Y = M11; row1.Z = M12; row1.W = M13;
			row2.X = M20; row2.Y = M21; row2.Z = M22; row2.W = M23;
			row3.X = M30; row3.Y = M31; row3.Z = M32; row3.W = M33;
		}

		void Matrix4::GetColumns(Vector4& column0, Vector4& column1, Vector4& column2, Vector4& column3) const
		{
			column0.X = M00; column0.Y = M10; column0.Z = M20; column0.W = M30;
			column1.X = M01; column1.Y = M11; column1.Z = M21; column1.W = M31;
			column2.X = M02; column2.Y = M12; column2.Z = M22; column2.W = M32;
			column3.X = M03; column3.Y = M13; column3.Z = M23; column3.W = M33;
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
			/*
			// Use for GREATER depth testing
			Real cot = static_cast<Real>(1) / std::tan(fovy / static_cast<Real>(2));
			Real diff = static_cast<Real>(1) / (far - near);

			return Matrix4{
				cot / aspect, static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), cot, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), -(far + near) * diff, static_cast<Real>(2) * far * near * diff,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0)
			};
			*/


			// Use for LESS depth testing
			Real cot = static_cast<Real>(1) / std::tan(fovy / static_cast<Real>(2));
			Real diff = static_cast<Real>(1) / (far - near);

			return Matrix4{
				cot / aspect, static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), cot, static_cast<Real>(0), static_cast<Real>(0),
				static_cast<Real>(0), static_cast<Real>(0), far * diff, -far * near * diff,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0)
			};
		}

		Matrix4 Matrix4::CreateOrtho(Real left, Real right, Real bottom, Real top, Real near, Real far)
		{
			Real Xmax = right - left;
			Real Ymax = top - bottom;
			Real Zmax = far - near;

			return Matrix4{
				static_cast<Real>(2) / Xmax,  static_cast<Real>(0), static_cast<Real>(0), -(right + left) / Xmax,
				static_cast<Real>(0), static_cast<Real>(2) / Ymax, static_cast<Real>(0), -(top + bottom) / Ymax,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(2) / Zmax, -(near + far) / Zmax,
				static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
			};
		}

		Matrix4 Matrix4::CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& upVector)
		{
			Vector3 zaxis = (cameraTarget - cameraPosition).GetNormalized();
			Vector3 xaxis = Vector3::CrossProduct(upVector, zaxis).GetNormalized();
			Vector3 yaxis = Vector3::CrossProduct(zaxis, xaxis);

			return Matrix4{
				xaxis.X, yaxis.X, zaxis.X, static_cast<Real>(0),
				xaxis.Y, yaxis.Y, zaxis.Y, static_cast<Real>(0),
				xaxis.Z, yaxis.Z, zaxis.Z, static_cast<Real>(0),
				-Vector3::DotProduct(xaxis, cameraPosition), -Vector3::DotProduct(yaxis, cameraPosition), -Vector3::DotProduct(zaxis, cameraPosition), static_cast<Real>(1)
			};

		//	return Matrix4{
		//		xaxis.X, xaxis.Y, xaxis.Z, -Vector3::DotProduct(xaxis, cameraPosition),
		//		yaxis.X, yaxis.Y, yaxis.Z, -Vector3::DotProduct(yaxis, cameraPosition),
		//		zaxis.X, zaxis.Y, zaxis.Z, -Vector3::DotProduct(zaxis, cameraPosition),
		//		static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1)
		//	};
		}

		Vector3 Matrix4::TransformVector(const Matrix4& matrix, const Vector3& vector)
		{
			return Vector3{
				matrix.M00 * vector.X + matrix.M01 * vector.Y + matrix.M02 * vector.Z,
				matrix.M10 * vector.X + matrix.M11 * vector.Y + matrix.M12 * vector.Z,
				matrix.M20 * vector.X + matrix.M21 * vector.Y + matrix.M22 * vector.Z
			};
		}

		Vector3 Matrix4::TransformPosition(const Matrix4& matrix, const Vector3& position)
		{
			return Vector3{
				matrix.M00 * position.X + matrix.M01 * position.Y + matrix.M02 * position.Z + matrix.M03,
				matrix.M10 * position.X + matrix.M11 * position.Y + matrix.M12 * position.Z + matrix.M13,
				matrix.M20 * position.X + matrix.M21 * position.Y + matrix.M22 * position.Z + matrix.M23
			};
		}

		Vector3 Matrix4::TransformNormal(const Matrix4& matrix, const Vector3& normal)
		{
			Matrix4 matInv = matrix.GetInversed();

			return Vector3{
				matInv.M00 * normal.X + matInv.M10 * normal.Y + matInv.M20 * normal.Z,
				matInv.M01 * normal.X + matInv.M11 * normal.Y + matInv.M21 * normal.Z,
				matInv.M02 * normal.X + matInv.M12 * normal.Y + matInv.M22 * normal.Z
			};
		}

		Vector3 Matrix4::TransformPerspective(const Matrix4& matrix, const Vector3& position)
		{
			Vector4 result = Vector4{ position, static_cast<Real>(1) };
			result = matrix * result;
			return static_cast<Vector3>(result) / result.W;
		}

#pragma endregion

#pragma region Operators

		Matrix4::operator Matrix3() const
		{
			return Matrix3{ M00, M01, M02, M10, M11, M12, M20, M21, M22 };
		}

		void Matrix4::operator += (const Matrix4& matrix)
		{
			M00 += matrix.M00;
			M01 += matrix.M01;
			M02 += matrix.M02;
			M03 += matrix.M03;
			M10 += matrix.M10;
			M11 += matrix.M11;
			M12 += matrix.M12;
			M13 += matrix.M13;
			M20 += matrix.M20;
			M21 += matrix.M21;
			M22 += matrix.M22;
			M23 += matrix.M23;
			M30 += matrix.M30;
			M31 += matrix.M31;
			M32 += matrix.M32;
			M33 += matrix.M33;

		}

		void Matrix4::operator -= (const Matrix4& matrix)
		{
			M00 -= matrix.M00;
			M01 -= matrix.M01;
			M02 -= matrix.M02;
			M03 -= matrix.M03;
			M10 -= matrix.M10;
			M11 -= matrix.M11;
			M12 -= matrix.M12;
			M13 -= matrix.M13;
			M20 -= matrix.M20;
			M21 -= matrix.M21;
			M22 -= matrix.M22;
			M23 -= matrix.M23;
			M30 -= matrix.M30;
			M31 -= matrix.M31;
			M32 -= matrix.M32;
			M33 -= matrix.M33;
		}

		void Matrix4::operator *= (Real scalar)
		{
			M00 *= scalar;
			M01 *= scalar;
			M02 *= scalar;
			M03 *= scalar;
			M10 *= scalar;
			M11 *= scalar;
			M12 *= scalar;
			M13 *= scalar;
			M20 *= scalar;
			M21 *= scalar;
			M22 *= scalar;
			M23 *= scalar;
			M30 *= scalar;
			M31 *= scalar;
			M32 *= scalar;
			M33 *= scalar;
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
				-matrix.M00, -matrix.M01, -matrix.M02, -matrix.M03,
				-matrix.M10, -matrix.M11, -matrix.M12, -matrix.M13,
				-matrix.M20, -matrix.M21, -matrix.M22, -matrix.M23,
				-matrix.M30, -matrix.M31, -matrix.M32, -matrix.M33
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
				lhs.M00 * rhs.X + lhs.M01 * rhs.Y + lhs.M02 * rhs.Z + lhs.M03 * rhs.W,
				lhs.M10 * rhs.X + lhs.M11 * rhs.Y + lhs.M12 * rhs.Z + lhs.M13 * rhs.W,
				lhs.M20 * rhs.X + lhs.M21 * rhs.Y + lhs.M22 * rhs.Z + lhs.M23 * rhs.W,
				lhs.M30 * rhs.X + lhs.M31 * rhs.Y + lhs.M32 * rhs.Z + lhs.M33 * rhs.W
			};
		}

		Matrix4 operator * (const Matrix4& lhs, const Matrix4& rhs)
		{
			return Matrix4{
				lhs.M00 * rhs.M00 + lhs.M01 * rhs.M10 + lhs.M02 * rhs.M20 + lhs.M03 * rhs.M30,
				lhs.M00 * rhs.M01 + lhs.M01 * rhs.M11 + lhs.M02 * rhs.M21 + lhs.M03 * rhs.M31,
				lhs.M00 * rhs.M02 + lhs.M01 * rhs.M12 + lhs.M02 * rhs.M22 + lhs.M03 * rhs.M32,
				lhs.M00 * rhs.M03 + lhs.M01 * rhs.M13 + lhs.M02 * rhs.M23 + lhs.M03 * rhs.M33,

				lhs.M10 * rhs.M00 + lhs.M11 * rhs.M10 + lhs.M12 * rhs.M20 + lhs.M13 * rhs.M30,
				lhs.M10 * rhs.M01 + lhs.M11 * rhs.M11 + lhs.M12 * rhs.M21 + lhs.M13 * rhs.M31,
				lhs.M10 * rhs.M02 + lhs.M11 * rhs.M12 + lhs.M12 * rhs.M22 + lhs.M13 * rhs.M32,
				lhs.M10 * rhs.M03 + lhs.M11 * rhs.M13 + lhs.M12 * rhs.M23 + lhs.M13 * rhs.M33,

				lhs.M20 * rhs.M00 + lhs.M21 * rhs.M10 + lhs.M22 * rhs.M20 + lhs.M23 * rhs.M30,
				lhs.M20 * rhs.M01 + lhs.M21 * rhs.M11 + lhs.M22 * rhs.M21 + lhs.M23 * rhs.M31,
				lhs.M20 * rhs.M02 + lhs.M21 * rhs.M12 + lhs.M22 * rhs.M22 + lhs.M23 * rhs.M32,
				lhs.M20 * rhs.M03 + lhs.M21 * rhs.M13 + lhs.M22 * rhs.M23 + lhs.M23 * rhs.M33,

				lhs.M30 * rhs.M00 + lhs.M31 * rhs.M10 + lhs.M32 * rhs.M20 + lhs.M33 * rhs.M30,
				lhs.M30 * rhs.M01 + lhs.M31 * rhs.M11 + lhs.M32 * rhs.M21 + lhs.M33 * rhs.M31,
				lhs.M30 * rhs.M02 + lhs.M31 * rhs.M12 + lhs.M32 * rhs.M22 + lhs.M33 * rhs.M32,
				lhs.M30 * rhs.M03 + lhs.M31 * rhs.M13 + lhs.M32 * rhs.M23 + lhs.M33 * rhs.M33
			};
		}

		Matrix4 operator / (const Matrix4& matrix, Real scalar)
		{
			Matrix4 ret = matrix;
			ret *= static_cast<Real>(1) / scalar;
			return ret;
		}

		bool operator == (const Matrix4& lhs, const Matrix4& rhs)
		{
		//	return 
		//		lhs.M00 == rhs.M00 && lhs.M01 == rhs.M01 && lhs.M02 == rhs.M02 && lhs.M03 == rhs.M03 &&
		//		lhs.M10 == rhs.M10 && lhs.M11 == rhs.M11 && lhs.M12 == rhs.M12 && lhs.M13 == rhs.M13 &&
		//		lhs.M20 == rhs.M20 && lhs.M21 == rhs.M21 && lhs.M22 == rhs.M22 && lhs.M23 == rhs.M23 &&
		//		lhs.M30 == rhs.M30 && lhs.M31 == rhs.M31 && lhs.M32 == rhs.M32 && lhs.M33 == rhs.M33;
			return
				Utils::EpsEqual(lhs.M00, rhs.M00) && Utils::EpsEqual(lhs.M01, rhs.M01) && Utils::EpsEqual(lhs.M02, rhs.M02) && Utils::EpsEqual(lhs.M03, rhs.M03) &&
				Utils::EpsEqual(lhs.M10, rhs.M10) && Utils::EpsEqual(lhs.M11, rhs.M11) && Utils::EpsEqual(lhs.M12, rhs.M12) && Utils::EpsEqual(lhs.M13, rhs.M13) &&
				Utils::EpsEqual(lhs.M20, rhs.M20) && Utils::EpsEqual(lhs.M21, rhs.M21) && Utils::EpsEqual(lhs.M22, rhs.M22) && Utils::EpsEqual(lhs.M23, rhs.M23) &&
				Utils::EpsEqual(lhs.M30, rhs.M30) && Utils::EpsEqual(lhs.M31, rhs.M31) && Utils::EpsEqual(lhs.M32, rhs.M32) && Utils::EpsEqual(lhs.M33, rhs.M33);
		}

		bool operator != (const Matrix4& lhs, const Matrix4& rhs)
		{
		//	return 
		//		lhs.M00 != rhs.M00 || lhs.M01 != rhs.M01 || lhs.M02 != rhs.M02 || lhs.M03 != rhs.M03 ||
		//		lhs.M10 != rhs.M10 || lhs.M11 != rhs.M11 || lhs.M12 != rhs.M12 || lhs.M13 != rhs.M13 ||
		//		lhs.M20 != rhs.M20 || lhs.M21 != rhs.M21 || lhs.M22 != rhs.M22 || lhs.M23 != rhs.M23 ||
		//		lhs.M30 != rhs.M30 || lhs.M31 != rhs.M31 || lhs.M32 != rhs.M32 || lhs.M33 != rhs.M33;
			return
				Utils::EpsNotEqual(lhs.M00, rhs.M00) || Utils::EpsNotEqual(lhs.M01, rhs.M01) || Utils::EpsNotEqual(lhs.M02, rhs.M02) || Utils::EpsNotEqual(lhs.M03, rhs.M03) ||
				Utils::EpsNotEqual(lhs.M10, rhs.M10) || Utils::EpsNotEqual(lhs.M11, rhs.M11) || Utils::EpsNotEqual(lhs.M12, rhs.M12) || Utils::EpsNotEqual(lhs.M13, rhs.M13) ||
				Utils::EpsNotEqual(lhs.M20, rhs.M20) || Utils::EpsNotEqual(lhs.M21, rhs.M21) || Utils::EpsNotEqual(lhs.M22, rhs.M22) || Utils::EpsNotEqual(lhs.M23, rhs.M23) ||
				Utils::EpsNotEqual(lhs.M30, rhs.M30) || Utils::EpsNotEqual(lhs.M31, rhs.M31) || Utils::EpsNotEqual(lhs.M32, rhs.M32) || Utils::EpsNotEqual(lhs.M33, rhs.M33);
		}

		std::istream& operator >> (std::istream& stream, Matrix4& matrix)
		{
			stream.ignore(2);
			stream >> matrix.M00;
			stream.ignore(1);
			stream >> matrix.M01;
			stream.ignore(1);
			stream >> matrix.M02;
			stream.ignore(1);
			stream >> matrix.M03;
			stream.ignore(3);
			stream >> matrix.M10;
			stream.ignore(1);
			stream >> matrix.M11;
			stream.ignore(1);
			stream >> matrix.M12;
			stream.ignore(1);
			stream >> matrix.M13;
			stream.ignore(3);
			stream >> matrix.M20;
			stream.ignore(1);
			stream >> matrix.M21;
			stream.ignore(1);
			stream >> matrix.M22;
			stream.ignore(1);
			stream >> matrix.M23;
			stream.ignore(3);
			stream >> matrix.M30;
			stream.ignore(1);
			stream >> matrix.M31;
			stream.ignore(1);
			stream >> matrix.M32;
			stream.ignore(1);
			stream >> matrix.M33;
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
				matrix.M00 << "," << matrix.M01 << "," << matrix.M02 << "," << matrix.M03 << "],[" <<
				matrix.M10 << "," << matrix.M11 << "," << matrix.M12 << "," << matrix.M13 << "],[" <<
				matrix.M20 << "," << matrix.M21 << "," << matrix.M22 << "," << matrix.M23 << "],[" <<
				matrix.M30 << "," << matrix.M31 << "," << matrix.M32 << "," << matrix.M33 << "]]";
		}

		std::ostream& operator <<= (std::ostream& stream, const Matrix4& matrix)
		{
			return stream.write(reinterpret_cast<const char*>(matrix.Values), sizeof(matrix.Values));
		}

#pragma endregion
	}
}