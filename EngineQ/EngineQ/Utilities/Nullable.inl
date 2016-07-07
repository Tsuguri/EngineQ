namespace EngineQ
{
	namespace Utilities
	{
		template<typename T>
		Nullable<T>::Nullable() :
			exists{ false }
		{
		}

		template<typename T>
		Nullable<T>::Nullable(const T& value) :
			exists{ true }
		{
			new(this->memory) T{ value };
		}

		template<typename T>
		Nullable<T>& Nullable<T>::operator = (const T& value)
		{
			if (this->exists)
				*reinterpret_cast<T*>(this->memory) = value;
			else
			{
				new(this->memory) T{ value };
				this->exists = true;
			}

			return *this;
		}

		template<typename T>
		Nullable<T>::Nullable(T&& value) :
			exists{ true }
		{
			new(this->memory) T{ std::move(value) };
		}

		template<typename T>
		Nullable<T>& Nullable<T>::operator = (T&& value)
		{
			if (this->exists)
				*reinterpret_cast<T*>(this->memory) = std::move(value);
			else
			{
				new(this->memory) T{ std::move(value) };
				this->exists = true;
			}

			return *this;
		}

		template<typename T>
		Nullable<T>::Nullable(nullval_t) :
			exists{ false }
		{
		}

		template<typename T>
		Nullable<T>& Nullable<T>::operator = (nullval_t)
		{
			if (this->exists)
			{
				reinterpret_cast<T*>(this->memory)->~T();
				this->exists = false;
			}

			return *this;
		}

		template<typename T>
		Nullable<T>::Nullable(const Nullable<T>& other) :
			exists{ other.exists }
		{
			if (other.exists)
				new(this->memory) T{ *reinterpret_cast<const T*>(other.memory) };
		}

		template<typename T>
		Nullable<T>& Nullable<T>::operator = (const Nullable<T>& other)
		{
			if (this->exists)
			{
				if (other.exists)
				{
					*reinterpret_cast<T*>(this->memory) = *reinterpret_cast<const T*>(other.memory);
				}
				else
				{
					reinterpret_cast<T*>(this->memory)->~T();
					this->exists = false;
				}
			}
			else
			{
				if (other.exists)
				{
					new(this->memory) T{ *reinterpret_cast<const T*>(other.memory) };
					this->exists = true;
				}
			}

			return *this;
		}

		template<typename T>
		Nullable<T>::Nullable(Nullable<T>&& other) :
			exists{ other.exists }
		{
			if (other.exists)
			{
				new(this->memory) T{ std::move(*reinterpret_cast<T*>(other.memory)) };
				other.exists = false;
			}
		}

		template<typename T>
		Nullable<T>& Nullable<T>::operator = (Nullable<T>&& other)
		{
			if (this->exists)
			{
				if (other.exists)
				{
					*reinterpret_cast<T*>(this->memory) = std::move(*reinterpret_cast<const T*>(other.memory));
					other.exists = false;
				}
				else
				{
					reinterpret_cast<T*>(this->memory)->~T();
					this->exists = false;
				}
			}
			else
			{
				if (other.exists)
				{
					new(this->memory) T{ std::move(*reinterpret_cast<const T*>(other.memory)) };
					this->exists = true;
					other.exists = false;
				}
			}

			return *this;
		}

		template<typename T>
		Nullable<T>::~Nullable()
		{
			if (this->exists)
				reinterpret_cast<T*>(this->memory)->~T();
		}

		template<typename T>
		T* Nullable<T>::operator -> ()
		{
			if (!this->exists)
				throw NullValueException{};

			return reinterpret_cast<T*>(this->memory);
		}

		template<typename T>
		T& Nullable<T>::operator *()
		{
			if (!this->exists)
				throw NullValueException{};

			return *reinterpret_cast<T*>(this->memory);
		}

		template<typename T>
		bool Nullable<T>::operator == (nullval_t) const
		{
			return !this->exists;
		}

		template<typename T>
		bool Nullable<T>::operator != (nullval_t) const
		{
			return this->exists;
		}

		template<typename T>
		bool Nullable<T>::operator == (const T& other) const
		{
			if (!this->exists)
				return false;

			return *reinterpret_cast<const T*>(this->memory) == other;
		}

		template<typename T>
		bool Nullable<T>::operator != (const T& other) const
		{
			if (!this->exists)
				return true;

			return *reinterpret_cast<const T*>(this->memory) != other;
		}

		template<typename T>
		Nullable<T>::operator T&() const
		{
			if (!this->exists)
				throw NullValueException{};

			return *reinterpret_cast<const T*>(this->memory);
		}

		template<typename T>
		Nullable<T>::operator T&()
		{
			if (!this->exists)
				throw NullValueException{};

			return *reinterpret_cast<T*>(this->memory);
		}

		template<typename T, typename ...Args>
		Nullable<T> MakeNullable(Args&& ...args)
		{
			return Nullable<T>{ T{ std::forward<Args>(args)... } };
		}

		template<typename T>
		Nullable<T> MakeNullableEmpty()
		{
			return Nullable<T>{};
		}
	}
}