#ifndef ENGINEQ_MATH_VECTOR4_HPP
#define ENGINEQ_MATH_VECTOR4_HPP

#include "../Utilities/StringHelpers.hpp"
#include "Types.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace EngineQ
{
	namespace Math
	{
		template<typename Type>
		struct Vector4t
		{
		#pragma region Fields

			union
			{
				struct
				{
					Type X;
					Type Y;
					Type Z;
					Type W;
				};

				struct
				{
					Type R;
					Type G;
					Type B;
					Type A;
				};

				Type Values[4];
			};

		#pragma endregion

		#pragma region Constructors

			explicit Vector4t();

			explicit Vector4t(Type value);

			explicit Vector4t(Type x, Type y, Type z, Type w);

			explicit Vector4t(const Vector2t<Type>& vector, Type z, Type w);

			explicit Vector4t(const Vector3t<Type>& vector, Type w);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector4t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector4t& vector1, const Vector4t& vector2);

			static Real Distance(const Vector4t& vector1, const Vector4t& vector2);

			static Vector4t GetZero();

			static Vector4t GetOne();

		#pragma endregion

		#pragma region Operators

			explicit operator Vector2t<Type>() const;

			explicit operator Vector3t<Type>() const;

			template<typename Type2>
			explicit operator Vector4t<Type2>() const;

			void operator += (const Vector4t& other);

			void operator -= (const Vector4t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector4t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector4t& other);

		#pragma endregion
		};

	#pragma region Static Operators

	//	template<typename Type, typename std::enable_if<std::is_unsigned<Type>::value>::type* = nullptr>
		template<typename Type>
		Vector4t<Type> operator -(const Vector4t<Type>& vector);

		template<typename Type>
		Vector4t<Type> operator +(const Vector4t<Type>& vector);

		template<typename Type>
		Vector4t<Type> operator +(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

		template<typename Type>
		Vector4t<Type> operator -(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

		template<typename Type>
		Vector4t<Type> operator *(const Vector4t<Type>& vector, Type scalar);

		template<typename Type>
		Vector4t<Type> operator *(Type scalar, const Vector4t<Type>& vector);

		template<typename Type>
		Vector4t<Type> operator *(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

		template<typename Type>
		Vector4t<Type> operator /(const Vector4t<Type>& vector, Type scalar);

		template<typename Type>
		Vector4t<Type> operator /(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2);

	#pragma endregion

	#pragma region Typedefs

		using Vector4i = Vector4t<int>;
		using Vector4f = Vector4t<float>;
		using Vector4d = Vector4t<double>;

		using Vector4 = Vector4t<Real>;

	#pragma endregion
	}
}

#include "Vector4.inl"

#pragma region Explicit Instantiation

namespace EngineQ
{
	namespace Math
	{
	#ifdef ENGINEQ_MATH_VECTOR4_INSTANTIATE
		template struct Vector4t<int>;
	//	template Vector4t<int>::operator Vector4t<float>() const;
	//	template Vector4t<int>::operator Vector4t<double>();
		template Vector4t<int> operator -(const Vector4t<int>& vector);
		template Vector4t<int> operator +(const Vector4t<int>& vector);
		template Vector4t<int> operator +(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		template Vector4t<int> operator -(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		template Vector4t<int> operator *(const Vector4t<int>& vector, const int scalar);
		template Vector4t<int> operator *(const int scalar, const Vector4t<int>& vector);
		template Vector4t<int> operator *(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		template Vector4t<int> operator /(const Vector4t<int>& vector, const int scalar);
		template Vector4t<int> operator /(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		template bool operator ==(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		template bool operator !=(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		
		template struct Vector4t<float>;
	//	template Vector4t<float>::operator Vector4t<int>() const;
	//	template Vector4t<float>::operator Vector4t<double>() const;
		template Vector4t<float> operator -(const Vector4t<float>& vector);
		template Vector4t<float> operator +(const Vector4t<float>& vector);
		template Vector4t<float> operator +(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		template Vector4t<float> operator -(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		template Vector4t<float> operator *(const Vector4t<float>& vector, const float scalar);
		template Vector4t<float> operator *(const float scalar, const Vector4t<float>& vector);
		template Vector4t<float> operator *(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		template Vector4t<float> operator /(const Vector4t<float>& vector, const float scalar);
		template Vector4t<float> operator /(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		template bool operator ==(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		template bool operator !=(const Vector4t<float>& vector1, const Vector4t<float>& vector2);

		template struct Vector4t<double>;
	//	template Vector4t<double>::operator Vector4t<int>() const;
	//	template Vector4t<double>::operator Vector4t<float>() const;
		template Vector4t<double> operator -(const Vector4t<double>& vector);
		template Vector4t<double> operator +(const Vector4t<double>& vector);
		template Vector4t<double> operator +(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		template Vector4t<double> operator -(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		template Vector4t<double> operator *(const Vector4t<double>& vector, const double scalar);
		template Vector4t<double> operator *(const double scalar, const Vector4t<double>& vector);
		template Vector4t<double> operator *(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		template Vector4t<double> operator /(const Vector4t<double>& vector, const double scalar);
		template Vector4t<double> operator /(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		template bool operator ==(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		template bool operator !=(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
	#else
		extern template struct Vector4t<int>;
		//	extern template Vector4t<int>::operator Vector4t<float>() const;
		//	extern template Vector4t<int>::operator Vector4t<double>();
		extern template Vector4t<int> operator -(const Vector4t<int>& vector);
		extern template Vector4t<int> operator +(const Vector4t<int>& vector);
		extern template Vector4t<int> operator +(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		extern template Vector4t<int> operator -(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		extern template Vector4t<int> operator *(const Vector4t<int>& vector, const int scalar);
		extern template Vector4t<int> operator *(const int scalar, const Vector4t<int>& vector);
		extern template Vector4t<int> operator *(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		extern template Vector4t<int> operator /(const Vector4t<int>& vector, const int scalar);
		extern template Vector4t<int> operator /(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		extern template bool operator ==(const Vector4t<int>& vector1, const Vector4t<int>& vector2);
		extern template bool operator !=(const Vector4t<int>& vector1, const Vector4t<int>& vector2);

		extern template struct Vector4t<float>;
		//	extern template Vector4t<float>::operator Vector4t<int>() const;
		//	extern template Vector4t<float>::operator Vector4t<double>() const;
		extern template Vector4t<float> operator -(const Vector4t<float>& vector);
		extern template Vector4t<float> operator +(const Vector4t<float>& vector);
		extern template Vector4t<float> operator +(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		extern template Vector4t<float> operator -(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		extern template Vector4t<float> operator *(const Vector4t<float>& vector, const float scalar);
		extern template Vector4t<float> operator *(const float scalar, const Vector4t<float>& vector);
		extern template Vector4t<float> operator *(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		extern template Vector4t<float> operator /(const Vector4t<float>& vector, const float scalar);
		extern template Vector4t<float> operator /(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		extern template bool operator ==(const Vector4t<float>& vector1, const Vector4t<float>& vector2);
		extern template bool operator !=(const Vector4t<float>& vector1, const Vector4t<float>& vector2);

		extern template struct Vector4t<double>;
		//	extern template Vector4t<double>::operator Vector4t<int>() const;
		//	extern template Vector4t<double>::operator Vector4t<float>() const;
		extern template Vector4t<double> operator -(const Vector4t<double>& vector);
		extern template Vector4t<double> operator +(const Vector4t<double>& vector);
		extern template Vector4t<double> operator +(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		extern template Vector4t<double> operator -(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		extern template Vector4t<double> operator *(const Vector4t<double>& vector, const double scalar);
		extern template Vector4t<double> operator *(const double scalar, const Vector4t<double>& vector);
		extern template Vector4t<double> operator *(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		extern template Vector4t<double> operator /(const Vector4t<double>& vector, const double scalar);
		extern template Vector4t<double> operator /(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		extern template bool operator ==(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
		extern template bool operator !=(const Vector4t<double>& vector1, const Vector4t<double>& vector2);
	#endif
	}
}

#pragma endregion

#endif // !ENGINEQ_MATH_VECTOR4_HPP
