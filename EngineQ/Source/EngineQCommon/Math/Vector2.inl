namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		Vector2_t<Type>::Vector2_t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		Vector2_t<Type>::Vector2_t(Type value)
			: X{ value }, Y{ value }
		{
		}

		template<typename Type>
		Vector2_t<Type>::Vector2_t(Type x, Type y)
			: X{ x }, Y{ y }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		Type Vector2_t<Type>::GetSum() const
		{
			return this->X + this->Y;
		}

		template<typename Type>
		Real Vector2_t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y));
		}

		template<typename Type>
		Type Vector2_t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y;
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetNormalized() const
		{
			Vector2_t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		void Vector2_t<Type>::Normalize()
		{
			Type length = static_cast<Type>(GetLength());

			if (length == static_cast<Type>(0))
				return;

			this->X /= length;
			this->Y /= length;
		}

		template<typename Type>
		std::string Vector2_t<Type>::ToString() const
		{
			return Utilities::ToString(*this);
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		Type Vector2_t<Type>::DistanceSquared(const Vector2_t& vector1, const Vector2_t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		Real Vector2_t<Type>::Distance(const Vector2_t& vector1, const Vector2_t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		Type Vector2_t<Type>::DotProduct(const Vector2_t& vector1, const Vector2_t& vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y;
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetZero()
		{
			return Vector2_t{ static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetOne()
		{
			return Vector2_t{ static_cast<Type>(1), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetLeft()
		{
			return Vector2_t{ static_cast<Type>(-1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetRight()
		{
			return Vector2_t{ static_cast<Type>(1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetUp()
		{
			return Vector2_t{ static_cast<Type>(0), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector2_t<Type> Vector2_t<Type>::GetDown()
		{
			return Vector2_t{ static_cast<Type>(0), static_cast<Type>(-1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		template<typename Type2>
		Vector2_t<Type>::operator Vector2_t<Type2>() const
		{
			return Vector2_t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y) };
		}

		template<typename Type>
		void Vector2_t<Type>::operator += (const Vector2_t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
		}

		template<typename Type>
		void Vector2_t<Type>::operator -= (const Vector2_t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
		}

		template<typename Type>
		void Vector2_t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
		}

		template<typename Type>
		void Vector2_t<Type>::operator *= (const Vector2_t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
		}

		template<typename Type>
		void Vector2_t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
		}

		template<typename Type>
		void Vector2_t<Type>::operator /= (const Vector2_t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		Vector2_t<Type> operator -(const Vector2_t<Type>& vector)
		{
			return Vector2_t<Type>{ -vector.X, -vector.Y };
		}

		template<typename Type>
		Vector2_t<Type> operator +(const Vector2_t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		Vector2_t<Type> operator +(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
			return Vector2_t<Type>{ vector1.X + vector2.X, vector1.Y + vector2.Y };
		}

		template<typename Type>
		Vector2_t<Type> operator -(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
			return Vector2_t<Type>{ vector1.X - vector2.X, vector1.Y - vector2.Y };
		}

		template<typename Type>
		Vector2_t<Type> operator *(const Vector2_t<Type>& vector, Type scalar)
		{
			return Vector2_t<Type>{ vector.X * scalar, vector.Y * scalar };
		}

		template<typename Type>
		Vector2_t<Type> operator *(Type scalar, const Vector2_t<Type>& vector)
		{
			return Vector2_t<Type>{ scalar * vector.X, scalar * vector.Y };
		}

		template<typename Type>
		Vector2_t<Type> operator *(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
			return Vector2_t<Type>{ vector1.X * vector2.X, vector1.Y * vector2.Y };
		}

		template<typename Type>
		Vector2_t<Type> operator /(const Vector2_t<Type>& vector, Type scalar)
		{
			return Vector2_t<Type>{ vector.X / scalar, vector.Y / scalar };
		}

		template<typename Type>
		Vector2_t<Type> operator /(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
			return Vector2_t<Type>{ vector1.X / vector2.X, vector1.Y / vector2.Y };
		}

		template<typename Type>
		bool operator ==(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
		//	return (vector1.X == vector2.X && vector1.Y == vector2.Y);
			return Utils::EpsEqual(vector1.X, vector2.X) && Utils::EpsEqual(vector1.Y, vector2.Y);
		}

		template<typename Type>
		bool operator !=(const Vector2_t<Type>& vector1, const Vector2_t<Type>& vector2)
		{
		//	return (vector1.X != vector2.X || vector1.Y != vector2.Y);
			return Utils::EpsNotEqual(vector1.X, vector2.X) || Utils::EpsNotEqual(vector1.Y, vector2.Y);
		}
		
		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector2_t<Type>& vector)
		{
			stream.ignore(1);
			stream >> vector.X;
			stream.ignore(1);
			stream >> vector.Y;
			stream.ignore(1);

			return stream;
		}

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector2_t<Type>& vector)
		{
			return stream.read(reinterpret_cast<char*>(&vector.Values), sizeof(vector.Values));
		}

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector2_t<Type>& vector)
		{
			return stream << "[" << vector.X << "," << vector.Y << "]";
		}

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector2_t<Type>& vector)
		{
			return stream.write(reinterpret_cast<const char*>(&vector.Values), sizeof(vector.Values));
		}

	#pragma endregion
	}
}