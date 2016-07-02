#ifndef ENGINEQ_MATH_VECTOR2_H
#define ENGINEQ_MATH_VECTOR2_H

#include "../Utilities.hpp"
#include "Types.hpp"

namespace EngineQ
{
	namespace Math
	{
		template<typename Type>
		struct Vector2t
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

			explicit Vector2t();

			explicit Vector2t(Type value);

			explicit Vector2t(Type x, Type y);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector2t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector2t& vector1, const Vector2t& vector2);

			static Real Distance(const Vector2t& vector1, const Vector2t& vector2);

			static Type DotProduct(const Vector2t& vector1, const Vector2t& vector2);

			static Vector2t GetZero();

			static Vector2t GetOne();

			static Vector2t GetLeft();

			static Vector2t GetRight();

			static Vector2t GetUp();

			static Vector2t GetDown();

		#pragma endregion

		#pragma region Operators

			template<typename Type2>
			explicit operator Vector2t<Type2>() const;

			void operator += (const Vector2t& other);

			void operator -= (const Vector2t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector2t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector2t& other);

		#pragma endregion
		};

	#pragma region Static Operators

		template<typename Type>
		Vector2t<Type> operator -(const Vector2t<Type>& vector);

		template<typename Type>
		Vector2t<Type> operator +(const Vector2t<Type>& vector);

		template<typename Type>
		Vector2t<Type> operator +(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

		template<typename Type>
		Vector2t<Type> operator -(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

		template<typename Type>
		Vector2t<Type> operator *(const Vector2t<Type>& vector, Type scalar);

		template<typename Type>
		Vector2t<Type> operator *(Type scalar, const Vector2t<Type>& vector);

		template<typename Type>
		Vector2t<Type> operator *(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

		template<typename Type>
		Vector2t<Type> operator /(const Vector2t<Type>& vector, Type scalar);

		template<typename Type>
		Vector2t<Type> operator /(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2);

	#pragma endregion

	#pragma region Typedefs

		using Vector2i = Vector2t<int>;
		using Vector2f = Vector2t<float>;
		using Vector2d = Vector2t<double>;

		using Vector2 = Vector2t<Real>;

	#pragma endregion
	}
}

#include "Vector2.inl"

#endif // !ENGINEQ_MATH_VECTOR2_H