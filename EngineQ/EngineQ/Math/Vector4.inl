namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		inline Vector4t<Type>::Vector4t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }, Z{ static_cast<Type>(0) }, W{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		inline Vector4t<Type>::Vector4t(Type value)
			: X{ value }, Y{ value }, Z{ value }, W{ value }
		{
		}

		template<typename Type>
		inline Vector4t<Type>::Vector4t(Type x, Type y, Type z, Type w)
			: X{ x }, Y{ y }, Z{ z }, W{ w }
		{
		}

		template<typename Type>
		inline Vector4t<Type>::Vector4t(const Vector2t<Type>& vector, Type z, Type w)
			: X{ vector.X }, Y{ vector.Y }, Z{ z }, W{ w }
		{
		}

		template<typename Type>
		inline Vector4t<Type>::Vector4t(const Vector3t<Type>& vector, Type w)
			: X{ vector.X }, Y{ vector.Y }, Z{ vector.Z }, W{ w }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		inline Type Vector4t<Type>::GetSum() const
		{
			return this->X + this->Y + this->Z + this->W;
		}

		template<typename Type>
		inline Real Vector4t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W));
		}

		template<typename Type>
		inline Type Vector4t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W;
		}

		template<typename Type>
		inline Vector4t<Type> Vector4t<Type>::GetNormalized() const
		{
			Vector4t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		inline void Vector4t<Type>::Normalize()
		{
			Type length = static_cast<Type>(GetLength());

			if (length == static_cast<Type>(0))
				return;

			this->X /= length;
			this->Y /= length;
			this->Z /= length;
			this->W /= length;
		}

		template<typename Type>
		inline std::string Vector4t<Type>::ToString() const
		{
			return "[" + EngineQ::ToString(this->X) + "," + EngineQ::ToString(this->Y) + "," + EngineQ::ToString(this->Z) + "," + EngineQ::ToString(this->W) + "]";
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		inline Type Vector4t<Type>::DistanceSquared(const Vector4t& vector1, const Vector4t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		inline Real Vector4t<Type>::Distance(const Vector4t& vector1, const Vector4t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		inline Vector4t<Type> Vector4t<Type>::GetZero()
		{
			return Vector4t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		inline Vector4t<Type> Vector4t<Type>::GetOne()
		{
			return Vector4t{ static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		inline Vector4t<Type>::operator Vector2t<Type>() const
		{
			return Vector2t<Type>{ this->X, this->Y };
		}

		template<typename Type>
		inline Vector4t<Type>::operator Vector3t<Type>() const
		{
			return Vector3t<Type>{ this->X, this->Y, this->Z };
		}

		template<typename Type>
		template<typename Type2>
		inline Vector4t<Type>::operator Vector4t<Type2>() const
		{
			return Vector4t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y), static_cast<Type2>(this->Z), static_cast<Type2>(this->W) };
		}

		template<typename Type>
		inline void Vector4t<Type>::operator += (const Vector4t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
			this->Z += other.Z;
			this->W += other.W;
		}

		template<typename Type>
		inline void Vector4t<Type>::operator -= (const Vector4t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
			this->Z -= other.Z;
			this->W -= other.W;
		}

		template<typename Type>
		inline void Vector4t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			this->Z *= scalar;
			this->W *= scalar;
		}

		template<typename Type>
		inline void Vector4t<Type>::operator *= (const Vector4t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
			this->Z *= other.Z;
			this->W *= other.W;
		}

		template<typename Type>
		inline void Vector4t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
			this->Z /= scalar;
			this->W /= scalar;
		}

		template<typename Type>
		inline void Vector4t<Type>::operator /= (const Vector4t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
			this->Z /= other.Z;
			this->W /= other.W;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		inline Vector4t<Type> operator -(const Vector4t<Type>& vector)
		{
			return Vector4t<Type>{ -vector.X, -vector.Y, -vector.Z, -vector.W };
		}

		template<typename Type>
		inline Vector4t<Type> operator +(const Vector4t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		inline Vector4t<Type> operator +(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return Vector4t<Type>{ vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z, vector1.W + vector2.W };
		}

		template<typename Type>
		inline Vector4t<Type> operator -(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return Vector4t<Type>{ vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z, vector1.W - vector2.W };
		}

		template<typename Type>
		inline Vector4t<Type> operator *(const Vector4t<Type>& vector, Type scalar)
		{
			return Vector4t<Type>{ vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar };
		}

		template<typename Type>
		inline Vector4t<Type> operator *(Type scalar, const Vector4t<Type>& vector)
		{
			return Vector4t<Type>{ scalar * vector.X, scalar * vector.Y, scalar * vector.Z, scalar * vector.W };
		}

		template<typename Type>
		inline Vector4t<Type> operator *(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return Vector4t<Type>{ vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z, vector1.W * vector2.W };
		}

		template<typename Type>
		inline Vector4t<Type> operator /(const Vector4t<Type>& vector, Type scalar)
		{
			return Vector4t<Type>{ vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar };
		}

		template<typename Type>
		inline Vector4t<Type> operator /(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return Vector4t<Type>{ vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z, vector1.W / vector2.W };
		}

		template<typename Type>
		inline bool operator ==(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z && vector1.W == vector2.W);
		}

		template<typename Type>
		inline bool operator !=(const Vector4t<Type>& vector1, const Vector4t<Type>& vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z || vector1.W != vector2.W);
		}

	#pragma endregion
	}
}