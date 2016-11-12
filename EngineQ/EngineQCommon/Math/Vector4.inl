namespace EngineQ
{
	namespace Math
	{
	#pragma region Constructors

		template<typename Type>
		Vector4_t<Type>::Vector4_t()
			: X{ static_cast<Type>(0) }, Y{ static_cast<Type>(0) }, Z{ static_cast<Type>(0) }, W{ static_cast<Type>(0) }
		{
		}

		template<typename Type>
		Vector4_t<Type>::Vector4_t(Type value)
			: X{ value }, Y{ value }, Z{ value }, W{ value }
		{
		}

		template<typename Type>
		Vector4_t<Type>::Vector4_t(Type x, Type y, Type z, Type w)
			: X{ x }, Y{ y }, Z{ z }, W{ w }
		{
		}

		template<typename Type>
		Vector4_t<Type>::Vector4_t(const Vector2_t<Type>& vector, Type z, Type w)
			: X{ vector.X }, Y{ vector.Y }, Z{ z }, W{ w }
		{
		}

		template<typename Type>
		Vector4_t<Type>::Vector4_t(const Vector3_t<Type>& vector, Type w)
			: X{ vector.X }, Y{ vector.Y }, Z{ vector.Z }, W{ w }
		{
		}

	#pragma endregion

	#pragma region Methods

		template<typename Type>
		Type Vector4_t<Type>::GetSum() const
		{
			return this->X + this->Y + this->Z + this->W;
		}

		template<typename Type>
		Real Vector4_t<Type>::GetLength() const
		{
			return std::sqrt(static_cast<Real>(this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W));
		}

		template<typename Type>
		Type Vector4_t<Type>::GetLengthSquared() const
		{
			return this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W;
		}

		template<typename Type>
		Vector4_t<Type> Vector4_t<Type>::GetNormalized() const
		{
			Vector4_t ret = *this;
			ret.Normalize();

			return ret;
		}

		template<typename Type>
		void Vector4_t<Type>::Normalize()
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
		std::string Vector4_t<Type>::ToString() const
		{
			return Utilities::ToString(*this);
		}

	#pragma endregion

	#pragma region Static Methods

		template<typename Type>
		Type Vector4_t<Type>::DistanceSquared(const Vector4_t& vector1, const Vector4_t& vector2)
		{
			return (vector2 - vector1).GetLengthSquared();
		}

		template<typename Type>
		Real Vector4_t<Type>::Distance(const Vector4_t& vector1, const Vector4_t& vector2)
		{
			return (vector2 - vector1).GetLength();
		}

		template<typename Type>
		Vector4_t<Type> Vector4_t<Type>::GetZero()
		{
			return Vector4_t{ static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0) };
		}

		template<typename Type>
		Vector4_t<Type> Vector4_t<Type>::GetOne()
		{
			return Vector4_t{ static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1) };
		}

	#pragma endregion

	#pragma region Operators

		template<typename Type>
		Vector4_t<Type>::operator Vector2_t<Type>() const
		{
			return Vector2_t<Type>{ this->X, this->Y };
		}

		template<typename Type>
		Vector4_t<Type>::operator Vector3_t<Type>() const
		{
			return Vector3_t<Type>{ this->X, this->Y, this->Z };
		}

		template<typename Type>
		template<typename Type2>
		Vector4_t<Type>::operator Vector4_t<Type2>() const
		{
			return Vector4_t<Type2>{ static_cast<Type2>(this->X), static_cast<Type2>(this->Y), static_cast<Type2>(this->Z), static_cast<Type2>(this->W) };
		}

		template<typename Type>
		void Vector4_t<Type>::operator += (const Vector4_t& other)
		{
			this->X += other.X;
			this->Y += other.Y;
			this->Z += other.Z;
			this->W += other.W;
		}

		template<typename Type>
		void Vector4_t<Type>::operator -= (const Vector4_t& other)
		{
			this->X -= other.X;
			this->Y -= other.Y;
			this->Z -= other.Z;
			this->W -= other.W;
		}

		template<typename Type>
		void Vector4_t<Type>::operator *= (Type scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			this->Z *= scalar;
			this->W *= scalar;
		}

		template<typename Type>
		void Vector4_t<Type>::operator *= (const Vector4_t& other)
		{
			this->X *= other.X;
			this->Y *= other.Y;
			this->Z *= other.Z;
			this->W *= other.W;
		}

		template<typename Type>
		void Vector4_t<Type>::operator /= (Type scalar)
		{
			this->X /= scalar;
			this->Y /= scalar;
			this->Z /= scalar;
			this->W /= scalar;
		}

		template<typename Type>
		void Vector4_t<Type>::operator /= (const Vector4_t& other)
		{
			this->X /= other.X;
			this->Y /= other.Y;
			this->Z /= other.Z;
			this->W /= other.W;
		}

	#pragma endregion

	#pragma region Static Operators

		template<typename Type>
		Vector4_t<Type> operator -(const Vector4_t<Type>& vector)
		{
			return Vector4_t<Type>{ -vector.X, -vector.Y, -vector.Z, -vector.W };
		}

		template<typename Type>
		Vector4_t<Type> operator +(const Vector4_t<Type>& vector)
		{
			return vector;
		}

		template<typename Type>
		Vector4_t<Type> operator +(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return Vector4_t<Type>{ vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z, vector1.W + vector2.W };
		}

		template<typename Type>
		Vector4_t<Type> operator -(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return Vector4_t<Type>{ vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z, vector1.W - vector2.W };
		}

		template<typename Type>
		Vector4_t<Type> operator *(const Vector4_t<Type>& vector, Type scalar)
		{
			return Vector4_t<Type>{ vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar };
		}

		template<typename Type>
		Vector4_t<Type> operator *(Type scalar, const Vector4_t<Type>& vector)
		{
			return Vector4_t<Type>{ scalar * vector.X, scalar * vector.Y, scalar * vector.Z, scalar * vector.W };
		}

		template<typename Type>
		Vector4_t<Type> operator *(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return Vector4_t<Type>{ vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z, vector1.W * vector2.W };
		}

		template<typename Type>
		Vector4_t<Type> operator /(const Vector4_t<Type>& vector, Type scalar)
		{
			return Vector4_t<Type>{ vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar };
		}

		template<typename Type>
		Vector4_t<Type> operator /(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return Vector4_t<Type>{ vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z, vector1.W / vector2.W };
		}

		template<typename Type>
		bool operator ==(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return (vector1.X == vector2.X && vector1.Y == vector2.Y && vector1.Z == vector2.Z && vector1.W == vector2.W);
		}

		template<typename Type>
		bool operator !=(const Vector4_t<Type>& vector1, const Vector4_t<Type>& vector2)
		{
			return (vector1.X != vector2.X || vector1.Y != vector2.Y || vector1.Z != vector2.Z || vector1.W != vector2.W);
		}
		
		template<typename Type>
		std::istream& operator >> (std::istream& stream, Vector4_t<Type>& vector)
		{
			stream.ignore(1);
			stream >> vector.X;
			stream.ignore(1);
			stream >> vector.Y;
			stream.ignore(1);
			stream >> vector.Z;
			stream.ignore(1);
			stream >> vector.W;
			stream.ignore(1);

			return stream;
		}

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Vector4_t<Type>& vector)
		{
			return stream.read(reinterpret_cast<char*>(&vector.Values), sizeof(vector.Values));
		}

		template<typename Type>
		std::ostream& operator << (std::ostream& stream, const Vector4_t<Type>& vector)
		{
			return stream << "[" << vector.X << "," << vector.Y << "," << vector.Z << "," << vector.W << "]";
		}

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Vector4_t<Type>& vector)
		{
			return stream.write(reinterpret_cast<const char*>(&vector.Values), sizeof(vector.Values));
		}

	#pragma endregion
	}
}