#ifndef ENGINEQ_MATH_VECTOR2_HPP
#define ENGINEQ_MATH_VECTOR2_HPP

#include "../Utilities/StringHelpers.hpp"
#include "Types.hpp"

namespace EngineQ
{
	namespace Math
	{
		template<typename Type>
		struct Vector2_t
		{
		#pragma region Fields
			
			union
			{
				struct
				{
					Type X;
					Type Y;
				};

				Type Values[2];
			};

		#pragma endregion

		#pragma region Constructors

			explicit Vector2_t();

			explicit Vector2_t(Type value);

			explicit Vector2_t(Type x, Type y);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector2_t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector2_t& vector1, const Vector2_t& vector2);

			static Real Distance(const Vector2_t& vector1, const Vector2_t& vector2);

			static Type DotProduct(const Vector2_t& vector1, const Vector2_t& vector2);

			static Vector2_t GetZero();

			static Vector2_t GetOne();

			static Vector2_t GetLeft();

			static Vector2_t GetRight();

			static Vector2_t GetUp();

			static Vector2_t GetDown();

		#pragma endregion

		#pragma region Operators

			template<typename Type2>
			explicit operator Vector2_t<Type2>() const;

			void operator += (const Vector2_t& other);

			void operator -= (const Vector2_t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector2_t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector2_t& other);

		#pragma endregion
		};

	#pragma region Static Operators

		template<typename Type>
		Vector2_t<Type> operator -(const Vector2_t<Type>& vector);

		template<typename Type>
		Vector2_t<Type> operator +(const Vector2_t<Type>& vector);

		template<typename Type>
		Vector2_t<Type> operator +(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		Vector2_t<Type> operator -(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		Vector2_t<Type> operator *(const Vector2_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector2_t<Type> operator *(Type scalar, const Vector2_t<Type>& vector);

		template<typename Type>
		Vector2_t<Type> operator *(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		Vector2_t<Type> operator /(const Vector2_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector2_t<Type> operator /(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2);

		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector2_t<Type>& vector);

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector2_t<Type>& vector);

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector2_t<Type>& vector);

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector2_t<Type>& vector);

	#pragma endregion

	#pragma region Typedefs

		using Vector2i = Vector2_t<int>;
		using Vector2f = Vector2_t<float>;
		using Vector2d = Vector2_t<double>;

		using Vector2 = Vector2_t<Real>;

	#pragma endregion
	}
}

#include "Vector2.inl"

#endif // !ENGINEQ_MATH_VECTOR2_HPP
