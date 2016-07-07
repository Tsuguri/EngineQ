namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		Vector3t<Type>::Vector3t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }, Z{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		Vector3t<Type>::Vector3t(Type value)
			: X{ value }, Y{ value }, Z{ value }
		{
		}

		template<typename Type>
		Vector3t<Type>::Vector3t(Type x, Type y, Type z)
			: X{ x }, Y{ y }, Z{ z }
		{
		}

		template<typename Type>
		Vector3t<Type>::Vector3t(const Vector2t<Type>& vector, Type z)
			: X{ vector.X }, Y{ vector.Y }, Z{ z }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		Type Vector3t<Type>::GetSum() const
		{
			return this->X + this->Y + this->Z;
		}

		template<typename Type>
		Real Vector3t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y + this->Z * this->Z));
		}

		template<typename Type>
		Type Vector3t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetNormalized() const
		{
			Vector3t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		void Vector3t<Type>::Normalize()
		{
			Type length = static_cast<Type>(GetLength());

			if (length == static_cast<Type>(0))
				return;

			this->X /= length;
			this->Y /= length;
			this->Z /= length;
		}

		template<typename Type>
		std::string Vector3t<Type>::ToString() const
		{
			return "[" + Utilities::ToString(this->X) + "," + Utilities::ToString(this->Y) + "," + Utilities::ToString(this->Z) + "]";
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		Type Vector3t<Type>::DistanceSquared(const Vector3t& vector1, const Vector3t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		Real Vector3t<Type>::Distance(const Vector3t& vector1, const Vector3t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		Type Vector3t<Type>::DotProduct(const Vector3t& vector1, const Vector3t& vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::CrossProduct(const Vector3t& vector1, const Vector3t& cector2)
		{
			return Vector3t{ vector1.Y * cector2.Z - cector2.Y * vector1.Z, vector1.Z * cector2.X - cector2.Z * vector1.X, vector1.X * cector2.Y - cector2.X * vector1.Y };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetZero()
		{
			return Vector3t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetOne()
		{
			return Vector3t{ static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetLeft()
		{
			return Vector3t{ static_cast<Type>(-1), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetRight()
		{
			return Vector3t{ static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetUp()
		{
			return Vector3t{ static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetDown()
		{
			return Vector3t{ static_cast<Type>(0), static_cast<Type>(-1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetForward()
		{
			return Vector3t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector3t<Type> Vector3t<Type>::GetBack()
		{
			return Vector3t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(-1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		Vector3t<Type>::operator Vector2t<Type>() const
		{
			return Vector2t<Type>{ this->X, this->Y };
		}

		template<typename Type>
		template<typename Type2>
		Vector3t<Type>::operator Vector3t<Type2>() const
		{
			return Vector3t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y), static_cast<Type2>(this->Z) };
		}

		template<typename Type>
		void Vector3t<Type>::operator += (const Vector3t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
			this->Z += other.Z;
		}

		template<typename Type>
		void Vector3t<Type>::operator -= (const Vector3t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
			this->Z -= other.Z;
		}

		template<typename Type>
		void Vector3t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			this->Z *= scalar;
		}

		template<typename Type>
		void Vector3t<Type>::operator *= (const Vector3t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
			this->Z *= other.Z;
		}

		template<typename Type>
		void Vector3t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
			this->Z /= scalar;
		}

		template<typename Type>
		void Vector3t<Type>::operator /= (const Vector3t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
			this->Z /= other.Z;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		Vector3t<Type> operator -(const Vector3t<Type>& vector)
		{
			return Vector3t<Type>{-vector.X, -vector.Y, -vector.Z};
		}

		template<typename Type>
		Vector3t<Type> operator +(const Vector3t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		Vector3t<Type> operator +(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return Vector3t<Type>{vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z};
		}

		template<typename Type>
		Vector3t<Type> operator -(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return Vector3t<Type>{vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z};
		}

		template<typename Type>
		Vector3t<Type> operator *(const Vector3t<Type>& vector, Type scalar)
		{
			return Vector3t<Type>{vector.X * scalar, vector.Y * scalar, vector.Z * scalar};
		}

		template<typename Type>
		Vector3t<Type> operator *(Type scalar, const Vector3t<Type>& vector)
		{
			return Vector3t<Type>{scalar * vector.X, scalar * vector.Y, scalar * vector.Z};
		}

		template<typename Type>
		Vector3t<Type> operator *(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return Vector3t<Type>{vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z};
		}

		template<typename Type>
		Vector3t<Type> operator /(const Vector3t<Type>& vector, Type scalar)
		{
			return Vector3t<Type>{vector.X / scalar, vector.Y / scalar, vector.Z / scalar};
		}

		template<typename Type>
		Vector3t<Type> operator /(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return Vector3t<Type>{vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z};
		}

		template<typename Type>
		bool operator ==(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z);
		}

		template<typename Type>
		bool operator !=(const Vector3t<Type>& vector1, const Vector3t<Type>& vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z);
		}

	#pragma endregion
	}
}