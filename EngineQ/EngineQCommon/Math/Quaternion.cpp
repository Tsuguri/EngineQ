#include "Quaternion.hpp"

#include "Vector3.hpp"
#include "Vector4.hpp"
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
			if (len < Utils::EPS<Real>)
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

			if (std::abs(sinVal - static_cast<Real>(1)) < Utils::EPS<Real>)
			{
				return Vector3{ -Utils::PI<Real> * static_cast<Real>(0.5), std::atan2(q1 * q2 - q0 * q3, q1 * q3 + q0 * q2), static_cast<Real>(0) };
			}
			if (std::abs(sinVal - static_cast<Real>(-1)) < Utils::EPS<Real>)
			{
				return Vector3{ Utils::PI<Real> * static_cast<Real>(0.5), -std::atan2(q1 * q2 - q0 * q3, q1 * q3 + q0 * q2), static_cast<Real>(0) };
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

			if (length < Utils::EPS<Real>)
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

		Quaternion Quaternion::CreateLookAt(const Vector3& sourcePoint, const Vector3& targetPoint)
		{
			Vector3 forwardVector = (targetPoint - sourcePoint).GetNormalized();

			Real dot = Vector3::DotProduct(Vector3::GetForward(), forwardVector);

			if (std::abs(dot - static_cast<Real>(-1)) < Utils::EPS<Real>)
			{
				Vector3 up = Vector3::GetUp();
				return Quaternion{ static_cast<Real>(0), up.X, up.Y, up.Z };
			}
			if (std::abs(dot - static_cast<Real>(1)) < Utils::EPS<Real>)
			{
				return GetIdentity();
			}

			Real rotAngle = std::acos(dot);
			Vector3 rotAxis = Vector3::CrossProduct(Vector3::GetForward(), forwardVector).GetNormalized();
			return CreateFromAxisAngle(rotAxis, rotAngle);
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
				if (lenSqrt < Utils::EPS<Real>)
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

		bool Quaternion::AreEquivalent(const Quaternion& q1, const Quaternion& q2)
		{
			return
				(Utils::EpsComp(q1.W, q2.W) && Utils::EpsComp(q1.X, q2.X) && Utils::EpsComp(q1.Y, q2.Y) && Utils::EpsComp(q1.Z, q2.Z)) ||
				(Utils::EpsComp(q1.W, -q2.W) && Utils::EpsComp(q1.X, -q2.X) && Utils::EpsComp(q1.Y, -q2.Y) && Utils::EpsComp(q1.Z, -q2.Z));
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

		bool operator ==(const Quaternion& q1, const Quaternion& q2)
		{
			return (q1.W == q2.W && q1.X == q2.X && q1.Y == q2.Y && q1.Z == q2.Z);
		}

		bool operator !=(const Quaternion& q1, const Quaternion& q2)
		{
			return (q1.W != q2.W || q1.X != q2.X || q1.Y != q2.Y || q1.Z != q2.Z);
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