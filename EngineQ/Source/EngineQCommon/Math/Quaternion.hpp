#ifndef ENGINEQ_MATH_QUATERNION_HPP
#define ENGINEQ_MATH_QUATERNION_HPP

// This project
#include "Types.hpp"
#include "EngineQCommon/Utilities/StringHelpers.hpp"


namespace EngineQ
{
	namespace Math
	{
		struct Quaternion
		{
		#pragma region Fields

			union
			{
				struct
				{
					Real W;
					Real X;
					Real Y;
					Real Z;
				};

				Real Values[4];
			};

		#pragma endregion

		#pragma region Constructors

			explicit Quaternion();
			explicit Quaternion(Real w, Real x, Real y, Real z);

		#pragma endregion

		#pragma region Methods

			Vector4 GetAxisAngle() const;
			Vector3 GetEulerAngles() const;
			Real GetLengthSquared() const;
			Real GetLength() const;
			Quaternion GetNormalized() const;

			void Normalize();
			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Quaternion CreateFromMatrix(const Matrix4& matrix);
			static Quaternion CreateLookAt(const Vector3& sourcePoint, const Vector3& targetPoint, const Vector3& up);
			static Quaternion CreateFromAxisAngle(const Vector3& axis, Real angle);
			static Quaternion CreateFromAxisAngle(Real x, Real y, Real z, Real angle);
			static Quaternion CreateRotationZ(Real angle);
			static Quaternion CreateRotationY(Real angle);
			static Quaternion CreateRotationX(Real angle);
			static Quaternion CreateFromEuler(Real x, Real y, Real z);
			static Quaternion CreateFromEuler(const Vector3& angles);
			static Quaternion GetIdentity();

		#pragma endregion

		#pragma region Operators

		#pragma endregion
		};

	#pragma region Static Operators

		Quaternion operator -(const Quaternion& q);
		Quaternion operator +(const Quaternion& q);
		Quaternion operator +(const Quaternion& q1, const Quaternion& q2);
		Quaternion operator -(const Quaternion& q1, const Quaternion& q2);
		Quaternion operator *(const Quaternion& q1, const Quaternion& q2);
		
		Vector4 operator *(const Quaternion& q, const Vector4& v);
		Vector3 operator *(const Quaternion& q, const Vector3& v);
		
		bool operator ==(const Quaternion& lhs, const Quaternion& rhs);
		bool operator !=(const Quaternion& lhs, const Quaternion& rhs);

		std::istream& operator >> (std::istream& stream, Quaternion& quaternion);
		std::istream& operator >>= (std::istream& stream, Quaternion& quaternion);

		std::ostream& operator << (std::ostream& stream, const Quaternion& quaternion);
		std::ostream& operator <<= (std::ostream& stream, const Quaternion& quaternion);

	#pragma endregion
	}
}

#endif // !ENGINEQ_MATH_QUATERNION_HPP
