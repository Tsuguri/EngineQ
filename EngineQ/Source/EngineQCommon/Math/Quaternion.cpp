#include "Quaternion.hpp"

// This project
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include "Utils.hpp"


namespace EngineQ
{
	namespace Math
	{
#pragma region Constructors

		Quaternion::Quaternion()
			: W{ static_cast<Real>(0) }, X{ static_cast<Real>(0) }, Y{ static_cast<Real>(0) }, Z{ static_cast<Real>(0) }
		{
		}

		Quaternion::Quaternion(Real w, Real x, Real y, Real z)
			: W{ w }, X{ x }, Y{ y }, Z{ z }
		{
		}

#pragma endregion

#pragma region Methods

		Vector4 Quaternion::GetAxisAngle() const
		{
			Real angle = static_cast<Real>(2) * std::acos(W);
			Real len = std::sqrt(static_cast<Real>(1) - W * W);
			if (len < Utils::Eps<Real>)
			{
				return Vector4{ static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) };
			}
			else
			{
				len = static_cast<Real>(1) / len;
				return Vector4{ X * len, Y * len, Z * len, angle };
			}
		}

		Vector3 Quaternion::GetEulerAngles() const
		{
			Real q0 = W;
			Real q1 = Z;
			Real q2 = X;
			Real q3 = Y;

			Real sinVal = static_cast<Real>(-2) * (q1 * q3 - q0 * q2);

			if (std::abs(sinVal - static_cast<Real>(1)) < Utils::Eps<Real>)
			{
				Real pi = Utils::PI<Real>;
				return Vector3{ -pi * static_cast<Real>(0.5), std::atan2(q1 * q2 - q0 * q3, q1 * q3 + q0 * q2), static_cast<Real>(0) };
			}
			if (std::abs(sinVal - static_cast<Real>(-1)) < Utils::Eps<Real>)
			{
				Real pi = Utils::PI<Real>;
				return Vector3{ pi * static_cast<Real>(0.5), -std::atan2(q1 * q2 - q0 * q3, q1 * q3 + q0 * q2), static_cast<Real>(0) };
			}

			return Vector3{
				std::asin(sinVal),
				std::atan2(q1 * q2 + q0 * q3, static_cast<Real>(0.5) - (q2 * q2 + q3 * q3)),
				std::atan2(q2 * q3 + q0 * q1, static_cast<Real>(0.5) - (q1 * q1 + q2 * q2))
			};
		}

		Real Quaternion::GetLengthSquared() const
		{
			return this->W * this->W + this->X * this->X + this->Y * this->Y + this->Z * this->Z;
		}

		Real Quaternion::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->W * this->W + this->X * this->X + this->Y * this->Y + this->Z * this->Z));
		}

		Quaternion Quaternion::GetNormalized() const
		{
			Quaternion ret = *this;
			ret.Normalize();

			return ret;
		}

		void Quaternion::Normalize()
		{
			Real length = GetLengthSquared();

			if (length < Utils::Eps<Real>)
			{
				this->W = static_cast<Real>(1);
				this->X = static_cast<Real>(0);
				this->Y = static_cast<Real>(0);
				this->Z = static_cast<Real>(0);
			}
			else
			{
				length = static_cast<Real>(1) / std::sqrt(length);

				this->X *= length;
				this->Y *= length;
				this->Z *= length;
				this->W *= length;
			}
		}

		std::string Quaternion::ToString() const
		{
			return Utilities::ToString(*this);
		}

#pragma endregion

#pragma region Static Methods

		Quaternion Quaternion::CreateLookAt(const Vector3& sourcePoint, const Vector3& targetPoint, const Vector3& up)
		{
			//	Vector3 forwardVector = (targetPoint - sourcePoint).GetNormalized();
			//
			//	Real dot = Vector3::DotProduct(Vector3::GetForward(), forwardVector);
			//
			//	if (std::abs(dot - static_cast<Real>(-1)) < Utils::Eps<Real>)
			//	{
			//		Vector3 up = Vector3::GetUp();
			//		return Quaternion{ static_cast<Real>(0), up.X, up.Y, up.Z };
			//	}
			//	if (std::abs(dot - static_cast<Real>(1)) < Utils::Eps<Real>)
			//	{
			//		return GetIdentity();
			//	}
			//
			//	Real rotAngle = std::acos(dot);
			//	Vector3 rotAxis = Vector3::CrossProduct(Vector3::GetForward(), forwardVector).GetNormalized();
			//	return CreateFromAxisAngle(rotAxis, rotAngle);

		//	Vector3 up = Vector3::GetUp();
		//
		//	// forward and size vectors of the coordinate frame 
		//	const Vector3 f = (sourcePoint - targetPoint).GetNormalized();
		//	const Vector3 side = (Vector3::CrossProduct(up, f)).GetNormalized();
		//
		//	// Vector3.CrossProduct product of bisection and [0, 0, -1] gives you the 
		//	// half-sine values required to orientate [0, 0, -1] to f
		//	// the Vector3.DotProduct product gives you half the cosine
		//	Vector3 b = (f + Vector3(0, 0, 1)).GetNormalized();
		//
		//	Vector3 bfcross = Vector3::CrossProduct(b, f);
		//	const Quaternion p = Quaternion(Vector3::DotProduct(b, f), bfcross.X, bfcross.Y, bfcross.Z);
		//
		//	// now we need an additional rotation around the f vector
		//	// to orientate the side vector.
		//	Vector3 r = Vector3{
		//		p.W*p.W + p.X*p.X - p.Y*p.Y - p.Z*p.Z,
		//		(2 * p.X * p.Y) - (2 * p.W * p.Z),
		//		2 * p.X * p.Z + 2 * p.W * p.Y
		//	};
		//
		//	b = (side + r).GetNormalized();
		//	Vector3 sidebcross = Vector3::CrossProduct(side, b);
		//	Quaternion q = Quaternion(Vector3::DotProduct(b, side), sidebcross.X, sidebcross.Y, sidebcross.Z);
		//	// now we can take the product of q and p
		//
		//	return p * q;

			return CreateFromMatrix(Matrix4::CreateLookAt(sourcePoint, targetPoint, up));
		}
		

		Quaternion Quaternion::CreateFromMatrix(const Matrix4& matrix)
		{
			Quaternion q;

			float trace = matrix(0, 0) + matrix(1, 1) + matrix(2, 2);
			if (trace > 0)
			{
				float s = 0.5f / std::sqrt(trace + 1.0f);
				q.W = 0.25f / s;
				q.X = (matrix(2, 1) - matrix(1, 2)) * s;
				q.Y = (matrix(0, 2) - matrix(2, 0)) * s;
				q.Z = (matrix(1, 0) - matrix(0, 1)) * s;
			}
			else
			{
				if (matrix(0, 0) > matrix(1, 1) && matrix(0, 0) > matrix(2, 2))
				{
					float s = 2.0f * std::sqrt(1.0f + matrix(0, 0) - matrix(1, 1) - matrix(2, 2));
					q.W = (matrix(2, 1) - matrix(1, 2)) / s;
					q.X = 0.25f * s;
					q.Y = (matrix(0, 1) + matrix(1, 0)) / s;
					q.Z = (matrix(0, 2) + matrix(2, 0)) / s;
				}
				else if (matrix(1, 1) > matrix(2, 2))
				{
					float s = 2.0f * std::sqrt(1.0f + matrix(1, 1) - matrix(0, 0) - matrix(2, 2));
					q.W = (matrix(0, 2) - matrix(2, 0)) / s;
					q.X = (matrix(0, 1) + matrix(1, 0)) / s;
					q.Y = 0.25f * s;
					q.Z = (matrix(1, 2) + matrix(2, 1)) / s;
				}
				else
				{
					float s = 2.0f * std::sqrt(1.0f + matrix(2, 2) - matrix(0, 0) - matrix(1, 1));
					q.W = (matrix(1, 0) - matrix(0, 1)) / s;
					q.X = (matrix(0, 2) + matrix(2, 0)) / s;
					q.Y = (matrix(1, 2) + matrix(2, 1)) / s;
					q.Z = 0.25f * s;
				}
			}

			return q;
		}

		Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axis, Real angle)
		{
			return CreateFromAxisAngle(axis.X, axis.Y, axis.Z, angle);
		}

		Quaternion Quaternion::CreateFromAxisAngle(Real x, Real y, Real z, Real angle)
		{
			angle *= static_cast<Real>(0.5);

			Real lenSqrt = x * x + y * y + z * z;
			if (lenSqrt != static_cast<Real>(1))
			{
				if (lenSqrt < Utils::Eps<Real>)
				{
					x = static_cast<Real>(1);
					y = static_cast<Real>(0);
					z = static_cast<Real>(0);
				}
				else
				{
					Real len = static_cast<Real>(1) / std::sqrt(lenSqrt);
					x *= len;
					y *= len;
					z *= len;
				}
			}

			Real s = std::sin(angle);

			return Quaternion{ std::cos(angle), s * x, s * y, s * z };
		}

		Quaternion Quaternion::CreateRotationZ(Real angle)
		{
			angle *= static_cast<Real>(0.5);

			return Quaternion{ std::cos(angle), static_cast<Real>(0), static_cast<Real>(0), std::sin(angle) };
		}

		Quaternion Quaternion::CreateRotationY(Real angle)
		{
			angle *= static_cast<Real>(0.5);

			return Quaternion{ std::cos(angle), static_cast<Real>(0), std::sin(angle), static_cast<Real>(0) };
		}

		Quaternion Quaternion::CreateRotationX(Real angle)
		{
			angle *= static_cast<Real>(0.5);

			return Quaternion{ std::cos(angle), std::sin(angle), static_cast<Real>(0), static_cast<Real>(0) };
		}

		Quaternion Quaternion::CreateFromEuler(Real x, Real y, Real z)
		{
			x *= static_cast<Real>(0.5);
			y *= static_cast<Real>(0.5);
			z *= static_cast<Real>(0.5);

			Real cosX = std::cos(x);
			Real sinX = std::sin(x);

			Real cosY = std::cos(y);
			Real sinY = std::sin(y);

			Real cosZ = std::cos(z);
			Real sinZ = std::sin(z);

			// Z -> X -> Y
			return Quaternion{
				cosY * cosX * cosZ + sinY * sinX * sinZ,
				cosY * sinX * cosZ + sinY * cosX * sinZ,
				sinY * cosX * cosZ - cosY * sinX * sinZ,
				cosY * cosX * sinZ - sinY * sinX * cosZ
			};
		}

		Quaternion Quaternion::CreateFromEuler(const Vector3& angles)
		{
			return CreateFromEuler(angles.X, angles.Y, angles.Z);
		}

		Quaternion Quaternion::GetIdentity()
		{
			return Quaternion{ static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) };
		}

#pragma endregion

#pragma region Operators

#pragma endregion

#pragma region Static Operators

		Quaternion operator +(const Quaternion& q)
		{
			return q;
		}

		Quaternion operator -(const Quaternion& q)
		{
			Quaternion q2 = q.GetNormalized();
			return Quaternion{ q2.W, -q2.X, -q2.Y, -q2.Z };
		}

		Quaternion operator +(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion{ q1.W + q2.W, q1.X + q2.X, q1.Y + q2.Y, q1.Z + q2.Z };
		}

		Quaternion operator -(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion{ q1.W - q2.W, q1.X - q2.X, q1.Y - q2.Y, q1.Z - q2.Z };
		}

		Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion{
				q1.W * q2.W - q1.X * q2.X - q1.Y * q2.Y - q1.Z * q2.Z,
				q1.W * q2.X + q1.X * q2.W + q1.Y * q2.Z - q1.Z * q2.Y,
				q1.W * q2.Y - q1.X * q2.Z + q1.Y * q2.W + q1.Z * q2.X,
				q1.W * q2.Z + q1.X * q2.Y - q1.Y * q2.X + q1.Z * q2.W
			};
		}

		Vector4 operator *(const Quaternion& q, const Vector4& v)
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

			return Vector4{
				(static_cast<Real>(1) - (yy + zz)) * v.X + (xy - wz) * v.Y + (xz + wy) * v.Z,
				(xy + wz) * v.X + (static_cast<Real>(1) - (xx + zz)) * v.Y + (yz - wx) * v.Z,
				(xz - wy) * v.X + (yz + wx) * v.Y + (static_cast<Real>(1) - (xx + yy)) * v.Z,
				v.W
			};
		}

		Vector3 operator *(const Quaternion& q, const Vector3& v)
		{
			Real num = q.X * static_cast<Real>(2);
			Real num2 = q.Y * static_cast<Real>(2);
			Real num3 = q.Z * static_cast<Real>(2);
			Real num4 = q.X * num;
			Real num5 = q.Y * num2;
			Real num6 = q.Z * num3;
			Real num7 = q.X * num2;
			Real num8 = q.X * num3;
			Real num9 = q.Y * num3;
			Real num10 = q.W * num;
			Real num11 = q.W * num2;
			Real num12 = q.W * num3;

			return Vector3{
				(static_cast<Real>(1) - (num5 + num6)) * v.X + (num7 - num12) * v.Y + (num8 + num11) * v.Z,
				(num7 + num12) * v.X + (static_cast<Real>(1) - (num4 + num6)) * v.Y + (num9 - num10) * v.Z,
				(num8 - num11) * v.X + (num9 + num10) * v.Y + (static_cast<Real>(1) - (num4 + num5)) * v.Z
			};
		}

		bool operator ==(const Quaternion& lhs, const Quaternion& rhs)
		{
			//	return (q1.W == q2.W && q1.X == q2.X && q1.Y == q2.Y && q1.Z == q2.Z);
			return
				(Utils::EpsEqual(lhs.W, rhs.W) && Utils::EpsEqual(lhs.X, rhs.X) && Utils::EpsEqual(lhs.Y, rhs.Y) && Utils::EpsEqual(lhs.Z, rhs.Z)) ||
				(Utils::EpsEqual(lhs.W, -rhs.W) && Utils::EpsEqual(lhs.X, -rhs.X) && Utils::EpsEqual(lhs.Y, -rhs.Y) && Utils::EpsEqual(lhs.Z, -rhs.Z));
		}

		bool operator !=(const Quaternion& lhs, const Quaternion& rhs)
		{
			//	return (q1.W != q2.W || q1.X != q2.X || q1.Y != q2.Y || q1.Z != q2.Z);
			return
				(Utils::EpsNotEqual(lhs.W, rhs.W) || Utils::EpsNotEqual(lhs.X, rhs.X) || Utils::EpsNotEqual(lhs.Y, rhs.Y) || Utils::EpsNotEqual(lhs.Z, rhs.Z)) &&
				(Utils::EpsNotEqual(lhs.W, -rhs.W) || Utils::EpsNotEqual(lhs.X, -rhs.X) || Utils::EpsNotEqual(lhs.Y, -rhs.Y) || Utils::EpsNotEqual(lhs.Z, -rhs.Z));
		}

		std::istream& operator >> (std::istream& stream, Quaternion& quaternion)
		{
			stream.ignore(1);
			stream >> quaternion.W;
			stream.ignore(1);
			stream >> quaternion.X;
			stream.ignore(1);
			stream >> quaternion.Y;
			stream.ignore(1);
			stream >> quaternion.Z;
			stream.ignore(1);

			return stream;
		}

		std::istream& operator >>= (std::istream& stream, Quaternion& quaternion)
		{
			return stream.read(reinterpret_cast<char*>(&quaternion.Values), sizeof(quaternion.Values));
		}

		std::ostream& operator << (std::ostream& stream, const Quaternion& quaternion)
		{
			return stream << "[" << quaternion.W << "," << quaternion.X << "," << quaternion.Y << "," << quaternion.Z << "]";
		}

		std::ostream& operator <<= (std::ostream& stream, const Quaternion& quaternion)
		{
			return stream.write(reinterpret_cast<const char*>(&quaternion.Values), sizeof(quaternion.Values));
		}

#pragma endregion
	}
}