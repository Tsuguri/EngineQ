#ifndef ENGINEQ_MATH_VECTOR4_HPP
#define ENGINEQ_MATH_VECTOR4_HPP

// This project
#include "Types.hpp"
#include "Utils.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "EngineQCommon/Utilities/StringHelpers.hpp"


namespace EngineQ
{
	namespace Math
	{
		template<typename Type>
		struct Vector4_t
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

			explicit Vector4_t();

			explicit Vector4_t(Type value);

			explicit Vector4_t(Type x, Type y, Type z, Type w);

			explicit Vector4_t(const Vector2_t<Type>& vector, Type z, Type w);

			explicit Vector4_t(const Vector3_t<Type>& vector, Type w);

		#pragma endregion

		#pragma region Methods

			Type GetSum() const;

			Real GetLength() const;

			Type GetLengthSquared() const;

			Vector4_t GetNormalized() const;

			void Normalize();

			std::string ToString() const;

		#pragma endregion

		#pragma region Static Methods

			static Type DistanceSquared(const Vector4_t& vector1, const Vector4_t& vector2);

			static Real Distance(const Vector4_t& vector1, const Vector4_t& vector2);

			static Vector4_t GetZero();

			static Vector4_t GetOne();

		#pragma endregion

		#pragma region Operators

			explicit operator Vector2_t<Type>() const;

			explicit operator Vector3_t<Type>() const;

			template<typename Type2>
			explicit operator Vector4_t<Type2>() const;

			void operator += (const Vector4_t& other);

			void operator -= (const Vector4_t& other);

			void operator *= (Type scalar);

			void operator *= (const Vector4_t& other);

			void operator /= (Type scalar);

			void operator /= (const Vector4_t& other);

		#pragma endregion
		};

	#pragma region Static Operators

	//	template<typename Type, typename std::enable_if<std::is_unsigned<Type>::value>::type* = nullptr>
		template<typename Type>
		Vector4_t<Type> operator -(const Vector4_t<Type>& vector);

		template<typename Type>
		Vector4_t<Type> operator +(const Vector4_t<Type>& vector);

		template<typename Type>
		Vector4_t<Type> operator +(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		Vector4_t<Type> operator -(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		Vector4_t<Type> operator *(const Vector4_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector4_t<Type> operator *(Type scalar, const Vector4_t<Type>& vector);

		template<typename Type>
		Vector4_t<Type> operator *(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		Vector4_t<Type> operator /(const Vector4_t<Type>& vector, Type scalar);

		template<typename Type>
		Vector4_t<Type> operator /(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		bool operator ==(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		bool operator !=(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2);

		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector4_t<Type>& vector);

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector4_t<Type>& vector);

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector4_t<Type>& vector);

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector4_t<Type>& vector);

	#pragma endregion

	#pragma region Typedefs

		using Vector4i = Vector4_t<int>;
		using Vector4f = Vector4_t<float>;
		using Vector4d = Vector4_t<double>;

		using Vector4 = Vector4_t<Real>;

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
		template struct Vector4_t<int>;
	//	template Vector4_t<int>::operator Vector4_t<float>() const;
	//	template Vector4_t<int>::operator Vector4_t<double>();
		template Vector4_t<int> operator -(const Vector4_t<int>& vector);
		template Vector4_t<int> operator +(const Vector4_t<int>& vector);
		template Vector4_t<int> operator +(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		template Vector4_t<int> operator -(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		template Vector4_t<int> operator *(const Vector4_t<int>& vector, const int scalar);
		template Vector4_t<int> operator *(const int scalar, const Vector4_t<int>& vector);
		template Vector4_t<int> operator *(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		template Vector4_t<int> operator /(const Vector4_t<int>& vector, const int scalar);
		template Vector4_t<int> operator /(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		template bool operator ==(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		template bool operator !=(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		
		template struct Vector4_t<float>;
	//	template Vector4_t<float>::operator Vector4_t<int>() const;
	//	template Vector4_t<float>::operator Vector4_t<double>() const;
		template Vector4_t<float> operator -(const Vector4_t<float>& vector);
		template Vector4_t<float> operator +(const Vector4_t<float>& vector);
		template Vector4_t<float> operator +(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		template Vector4_t<float> operator -(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		template Vector4_t<float> operator *(const Vector4_t<float>& vector, const float scalar);
		template Vector4_t<float> operator *(const float scalar, const Vector4_t<float>& vector);
		template Vector4_t<float> operator *(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		template Vector4_t<float> operator /(const Vector4_t<float>& vector, const float scalar);
		template Vector4_t<float> operator /(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		template bool operator ==(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		template bool operator !=(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);

		template struct Vector4_t<double>;
	//	template Vector4_t<double>::operator Vector4_t<int>() const;
	//	template Vector4_t<double>::operator Vector4_t<float>() const;
		template Vector4_t<double> operator -(const Vector4_t<double>& vector);
		template Vector4_t<double> operator +(const Vector4_t<double>& vector);
		template Vector4_t<double> operator +(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		template Vector4_t<double> operator -(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		template Vector4_t<double> operator *(const Vector4_t<double>& vector, const double scalar);
		template Vector4_t<double> operator *(const double scalar, const Vector4_t<double>& vector);
		template Vector4_t<double> operator *(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		template Vector4_t<double> operator /(const Vector4_t<double>& vector, const double scalar);
		template Vector4_t<double> operator /(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		template bool operator ==(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		template bool operator !=(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
	#else
		extern template struct Vector4_t<int>;
		//	extern template Vector4_t<int>::operator Vector4_t<float>() const;
		//	extern template Vector4_t<int>::operator Vector4_t<double>();
		extern template Vector4_t<int> operator -(const Vector4_t<int>& vector);
		extern template Vector4_t<int> operator +(const Vector4_t<int>& vector);
		extern template Vector4_t<int> operator +(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		extern template Vector4_t<int> operator -(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		extern template Vector4_t<int> operator *(const Vector4_t<int>& vector, int scalar);
		extern template Vector4_t<int> operator *(int scalar, const Vector4_t<int>& vector);
		extern template Vector4_t<int> operator *(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		extern template Vector4_t<int> operator /(const Vector4_t<int>& vector, int scalar);
		extern template Vector4_t<int> operator /(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		extern template bool operator ==(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);
		extern template bool operator !=(const Vector4_t<int>& vector1, const Vector4_t<int>& vector2);

		extern template struct Vector4_t<float>;
		//	extern template Vector4_t<float>::operator Vector4_t<int>() const;
		//	extern template Vector4_t<float>::operator Vector4_t<double>() const;
		extern template Vector4_t<float> operator -(const Vector4_t<float>& vector);
		extern template Vector4_t<float> operator +(const Vector4_t<float>& vector);
		extern template Vector4_t<float> operator +(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		extern template Vector4_t<float> operator -(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		extern template Vector4_t<float> operator *(const Vector4_t<float>& vector, float scalar);
		extern template Vector4_t<float> operator *(float scalar, const Vector4_t<float>& vector);
		extern template Vector4_t<float> operator *(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		extern template Vector4_t<float> operator /(const Vector4_t<float>& vector, float scalar);
		extern template Vector4_t<float> operator /(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		extern template bool operator ==(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);
		extern template bool operator !=(const Vector4_t<float>& vector1, const Vector4_t<float>& vector2);

		extern template struct Vector4_t<double>;
		//	extern template Vector4_t<double>::operator Vector4_t<int>() const;
		//	extern template Vector4_t<double>::operator Vector4_t<float>() const;
		extern template Vector4_t<double> operator -(const Vector4_t<double>& vector);
		extern template Vector4_t<double> operator +(const Vector4_t<double>& vector);
		extern template Vector4_t<double> operator +(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		extern template Vector4_t<double> operator -(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		extern template Vector4_t<double> operator *(const Vector4_t<double>& vector, double scalar);
		extern template Vector4_t<double> operator *(double scalar, const Vector4_t<double>& vector);
		extern template Vector4_t<double> operator *(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		extern template Vector4_t<double> operator /(const Vector4_t<double>& vector, double scalar);
		extern template Vector4_t<double> operator /(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		extern template bool operator ==(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
		extern template bool operator !=(const Vector4_t<double>& vector1, const Vector4_t<double>& vector2);
	#endif
	}
}

#pragma endregion

#endif // !ENGINEQ_MATH_VECTOR4_HPP
