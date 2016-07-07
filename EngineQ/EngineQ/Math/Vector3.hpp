#ifndef ENGINEQ_MATH_VECTOR3_HPP
#define ENGINEQ_MATH_VECTOR3_HPP

#include "../Utilities/StringHelpers.hpp"
#include "Types.hpp"

#include "Vector2.hpp"

namespace EngineQ
{
	namespace Math
	{
		template<typename Type>
		struct Vector3t
		{
		#pragma region Fields
			union
			{
				struct
				{
					Type X;
					Type Y;
					Type Z;
				};

				struct
				{
					Type R;
					Type G;
					Type B;
				};

				Type Values[3];
			};

		#pragma endregion

		#pragma region Constructors

			explicit Vector3t();

			explicit Vector3t(Type value);

			explicit Vector3t(Type x, Type y, Type z);

			explicit Vector3t(const Vector2t<Type>& vector, Type z);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector3t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector3t& vector1, const Vector3t& vector2);

			static Real Distance(const Vector3t& vector1, const Vector3t& vector2);

			static Type DotProduct(const Vector3t& vector1, const Vector3t& vector2);

			static Vector3t CrossProduct(const Vector3t& vector1, const Vector3t& vector2);

			static Vector3t GetZero();

			static Vector3t GetOne();

			static Vector3t GetLeft();

			static Vector3t GetRight();

			static Vector3t GetUp();

			static Vector3t GetDown();

			static Vector3t GetForward();

			static Vector3t GetBack();

		#pragma endregion

		#pragma region Operators

			explicit operator Vector2t<Type>() const;

			template<typename Type2>
			explicit operator Vector3t<Type2>() const;

			void operator += (const Vector3t& other);

			void operator -= (const Vector3t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector3t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector3t& other);

		#pragma endregion
		};

	#pragma region Static Operators

		template<typename Type>
		Vector3t<Type> operator -(const Vector3t<Type>& vector);

		template<typename Type>
		Vector3t<Type> operator +(const Vector3t<Type>& vector);

		template<typename Type>
		Vector3t<Type> operator +(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

		template<typename Type>
		Vector3t<Type> operator -(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

		template<typename Type>
		Vector3t<Type> operator *(const Vector3t<Type>& vector, Type scalar);

		template<typename Type>
		Vector3t<Type> operator *(Type scalar, const Vector3t<Type>& vector);

		template<typename Type>
		Vector3t<Type> operator *(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

		template<typename Type>
		Vector3t<Type> operator /(const Vector3t<Type>& vector, Type scalar);

		template<typename Type>
		Vector3t<Type> operator /(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2);

	#pragma endregion

	#pragma region Typedefs

		typedef Vector3t<int> Vector3i;
		typedef Vector3t<float> Vector3f;
		typedef Vector3t<double> Vector3d;

		typedef Vector3t<Real> Vector3;

	#pragma endregion
	}
}

#include "Vector3.inl"

#endif // !ENGINEQ_MATH_VECTOR3_HPP
