namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		Vector3_t<Type>::Vector3_t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }, Z{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		Vector3_t<Type>::Vector3_t(Type value)
			: X{ value }, Y{ value }, Z{ value }
		{
		}

		template<typename Type>
		Vector3_t<Type>::Vector3_t(Type x, Type y, Type z)
			: X{ x }, Y{ y }, Z{ z }
		{
		}

		template<typename Type>
		Vector3_t<Type>::Vector3_t(const Vector2_t<Type>& vector, Type z)
			: X{ vector.X }, Y{ vector.Y }, Z{ z }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		Type Vector3_t<Type>::GetSum() const
		{
			return this->X + this->Y + this->Z;
		}

		template<typename Type>
		Real Vector3_t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y + this->Z * this->Z));
		}

		template<typename Type>
		Type Vector3_t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetNormalized() const
		{
			Vector3_t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		void Vector3_t<Type>::Normalize()
		{
			Type length = static_cast<Type>(GetLength());

			if (length == static_cast<Type>(0))
				return;

			this->X /= length;
			this->Y /= length;
			this->Z /= length;
		}

		template<typename Type>
		std::string Vector3_t<Type>::ToString() const
		{
			return Utilities::ToString(*this);
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		Type Vector3_t<Type>::DistanceSquared(const Vector3_t& vector1, const Vector3_t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		Real Vector3_t<Type>::Distance(const Vector3_t& vector1, const Vector3_t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		Type Vector3_t<Type>::DotProduct(const Vector3_t& vector1, const Vector3_t& vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::CrossProduct(const Vector3_t& vector1, const Vector3_t& cector2)
		{
			return Vector3_t{ vector1.Y * cector2.Z - cector2.Y * vector1.Z, vector1.Z * cector2.X - cector2.Z * vector1.X, vector1.X * cector2.Y - cector2.X * vector1.Y };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetZero()
		{
			return Vector3_t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetOne()
		{
			return Vector3_t{ static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetLeft()
		{
			return Vector3_t{ static_cast<Type>(-1), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetRight()
		{
			return Vector3_t{ static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetUp()
		{
			return Vector3_t{ static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetDown()
		{
			return Vector3_t{ static_cast<Type>(0), static_cast<Type>(-1), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetForward()
		{
			return Vector3_t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1) };
		}

		template<typename Type>
		Vector3_t<Type> Vector3_t<Type>::GetBack()
		{
			return Vector3_t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(-1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		Vector3_t<Type>::operator Vector2_t<Type>() const
		{
			return Vector2_t<Type>{ this->X, this->Y };
		}

		template<typename Type>
		template<typename Type2>
		Vector3_t<Type>::operator Vector3_t<Type2>() const
		{
			return Vector3_t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y), static_cast<Type2>(this->Z) };
		}

		template<typename Type>
		void Vector3_t<Type>::operator += (const Vector3_t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
			this->Z += other.Z;
		}

		template<typename Type>
		void Vector3_t<Type>::operator -= (const Vector3_t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
			this->Z -= other.Z;
		}

		template<typename Type>
		void Vector3_t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			this->Z *= scalar;
		}

		template<typename Type>
		void Vector3_t<Type>::operator *= (const Vector3_t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
			this->Z *= other.Z;
		}

		template<typename Type>
		void Vector3_t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
			this->Z /= scalar;
		}

		template<typename Type>
		void Vector3_t<Type>::operator /= (const Vector3_t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
			this->Z /= other.Z;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		Vector3_t<Type> operator -(const Vector3_t<Type>& vector)
		{
			return Vector3_t<Type>{-vector.X, -vector.Y, -vector.Z};
		}

		template<typename Type>
		Vector3_t<Type> operator +(const Vector3_t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		Vector3_t<Type> operator +(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return Vector3_t<Type>{vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z};
		}

		template<typename Type>
		Vector3_t<Type> operator -(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return Vector3_t<Type>{vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z};
		}

		template<typename Type>
		Vector3_t<Type> operator *(const Vector3_t<Type>& vector, Type scalar)
		{
			return Vector3_t<Type>{vector.X * scalar, vector.Y * scalar, vector.Z * scalar};
		}

		template<typename Type>
		Vector3_t<Type> operator *(Type scalar, const Vector3_t<Type>& vector)
		{
			return Vector3_t<Type>{scalar * vector.X, scalar * vector.Y, scalar * vector.Z};
		}

		template<typename Type>
		Vector3_t<Type> operator *(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return Vector3_t<Type>{vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z};
		}

		template<typename Type>
		Vector3_t<Type> operator /(const Vector3_t<Type>& vector, Type scalar)
		{
			return Vector3_t<Type>{vector.X / scalar, vector.Y / scalar, vector.Z / scalar};
		}

		template<typename Type>
		Vector3_t<Type> operator /(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return Vector3_t<Type>{vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z};
		}

		template<typename Type>
		bool operator ==(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z);
		}

		template<typename Type>
		bool operator !=(const Vector3_t<Type>& vector1, const Vector3_t<Type>& vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z);
		}

		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector3_t<Type>& vector)
		{
			stream.ignore(1);
			stream >> vector.X;
			stream.ignore(1);
			stream >> vector.Y;
			stream.ignore(1);
			stream >> vector.Z;
			stream.ignore(1);

			return stream;
		}

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector3_t<Type>& vector)
		{
			return stream.read(reinterpret_cast<char*>(&vector.Values), sizeof(vector.Values));
		}

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector3_t<Type>& vector)
		{
			return stream << "[" << vector.X << "," << vector.Y << "," << vector.Z << "]";
		}

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector3_t<Type>& vector)
		{
			return stream.write(reinterpret_cast<const char*>(&vector.Values), sizeof(vector.Values));
		}

	#pragma endregion
	}
}