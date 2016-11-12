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
		struct Vector3_t
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

			explicit Vector3_t();

			explicit Vector3_t(Type value);

			explicit Vector3_t(Type x, Type y, Type z);

			explicit Vector3_t(const Vector2_t<Type>& vector, Type z);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector3_t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector3_t& vector1, const Vector3_t& vector2);

			static Real Distance(const Vector3_t& vector1, const Vector3_t& vector2);

			static Type DotProduct(const Vector3_t& vector1, const Vector3_t& vector2);

			static Vector3_t CrossProduct(const Vector3_t& vector1, const Vector3_t& vector2);

			static Vector3_t GetZero();

			static Vector3_t GetOne();

			static Vector3_t GetLeft();

			static Vector3_t GetRight();

			static Vector3_t GetUp();

			static Vector3_t GetDown();

			static Vector3_t GetForward();

			static Vector3_t GetBack();

		#pragma endregion

		#pragma region Operators

			explicit operator Vector2_t<Type>() const;

			template<typename Type2>
			explicit operator Vector3_t<Type2>() const;

			void operator += (const Vector3_t& other);

			void operator -= (const Vector3_t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector3_t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector3_t& other);

		#pragma endregion
		};

	#pragma region Static Operators

		template<typename Type>
		Vector3_t<Type> operator -(const Vector3_t<Type>& vector);

		template<typename Type>
		Vector3_t<Type> operator +(const Vector3_t<Type>& vector);

		template<typename Type>
		Vector3_t<Type> operator +(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		Vector3_t<Type> operator -(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		Vector3_t<Type> operator *(const Vector3_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector3_t<Type> operator *(Type scalar, const Vector3_t<Type>& vector);

		template<typename Type>
		Vector3_t<Type> operator *(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		Vector3_t<Type> operator /(const Vector3_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector3_t<Type> operator /(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2);

		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector3_t<Type>& vector);

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector3_t<Type>& vector);

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector3_t<Type>& vector);

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector3_t<Type>& vector);

	#pragma endregion

	#pragma region Typedefs

		typedef Vector3_t<int> Vector3i;
		typedef Vector3_t<float> Vector3f;
		typedef Vector3_t<double> Vector3d;

		typedef Vector3_t<Real> Vector3;

	#pragma endregion
	}
}

#include "Vector3.inl"

#endif // !ENGINEQ_MATH_VECTOR3_HPP
