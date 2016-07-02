namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		Vector2t<Type>::Vector2t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		Vector2t<Type>::Vector2t(Type value)
			: X{ value }, Y{ value }
		{
		}

		template<typename Type>
		Vector2t<Type>::Vector2t(Type x, Type y)
			: X{ x }, Y{ y }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		Type Vector2t<Type>::GetSum() const
		{
			return this->X + this->Y;
		}

		template<typename Type>
		Real Vector2t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y));
		}

		template<typename Type>
		Type Vector2t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y;
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetNormalized() const
		{
			Vector2t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		void Vector2t<Type>::Normalize()
		{
			Type length = static_cast<Type>(GetLength());

			if (length == static_cast<Type>(0))
				return;

			this->X /= length;
			this->Y /= length;
		}

		template<typename Type>
		std::string Vector2t<Type>::ToString() const
		{
			return "[" + EngineQ::ToString(this->X) + "," + EngineQ::ToString(this->Y) + "]";
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		Type Vector2t<Type>::DistanceSquared(const Vector2t& vector1, const Vector2t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		Real Vector2t<Type>::Distance(const Vector2t& vector1, const Vector2t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		Type Vector2t<Type>::DotProduct(const Vector2t& vector1, const Vector2t& vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y;
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetZero()
		{
			return Vector2t{ static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetOne()
		{
			return Vector2t{ static_cast<Type>(1), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetLeft()
		{
			return Vector2t{ static_cast<Type>(-1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetRight()
		{
			return Vector2t{ static_cast<Type>(1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetUp()
		{
			return Vector2t{ static_cast<Type>(0), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector2t<Type> Vector2t<Type>::GetDown()
		{
			return Vector2t{ static_cast<Type>(0), static_cast<Type>(-1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		template<typename Type2>
		Vector2t<Type>::operator Vector2t<Type2>() const
		{
			return Vector2t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y) };
		}

		template<typename Type>
		void Vector2t<Type>::operator += (const Vector2t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
		}

		template<typename Type>
		void Vector2t<Type>::operator -= (const Vector2t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
		}

		template<typename Type>
		void Vector2t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
		}

		template<typename Type>
		void Vector2t<Type>::operator *= (const Vector2t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
		}

		template<typename Type>
		void Vector2t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
		}

		template<typename Type>
		void Vector2t<Type>::operator /= (const Vector2t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		Vector2t<Type> operator -(const Vector2t<Type>& vector)
		{
			return Vector2t<Type>{ -vector.X, -vector.Y };
		}

		template<typename Type>
		Vector2t<Type> operator +(const Vector2t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		Vector2t<Type> operator +(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return Vector2t<Type>{ vector1.X + vector2.X, vector1.Y + vector2.Y };
		}

		template<typename Type>
		Vector2t<Type> operator -(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return Vector2t<Type>{ vector1.X - vector2.X, vector1.Y - vector2.Y };
		}

		template<typename Type>
		Vector2t<Type> operator *(const Vector2t<Type>& vector, Type scalar)
		{
			return Vector2t<Type>{ vector.X * scalar, vector.Y * scalar };
		}

		template<typename Type>
		Vector2t<Type> operator *(Type scalar, const Vector2t<Type>& vector)
		{
			return Vector2t<Type>{ scalar * vector.X, scalar * vector.Y };
		}

		template<typename Type>
		Vector2t<Type> operator *(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return Vector2t<Type>{ vector1.X * vector2.X, vector1.Y * vector2.Y };
		}

		template<typename Type>
		Vector2t<Type> operator /(const Vector2t<Type>& vector, Type scalar)
		{
			return Vector2t<Type>{ vector.X / scalar, vector.Y / scalar };
		}

		template<typename Type>
		Vector2t<Type> operator /(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return Vector2t<Type>{ vector1.X / vector2.X, vector1.Y / vector2.Y };
		}

		template<typename Type>
		bool operator ==(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y);
		}

		template<typename Type>
		bool operator !=(const Vector2t<Type>& vector1, const Vector2t<Type>& vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y);
		}

	#pragma endregion
	}
}