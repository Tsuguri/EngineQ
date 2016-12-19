#include "ObjectDestructor.hpp"


namespace Utilities
{
	template<typename Type>
	void Nullable<Type>::Destruct(Type* ptr)
	{
		ObjectDestructor<Type>::Destruct(*ptr);
	}

	template<typename Type>
	Nullable<Type>::Nullable() :
		exists{ false }
	{
	}

	template<typename Type>
	Nullable<Type>::Nullable(const Type& value) :
		exists{ true }
	{
		new(this->memory) Type{ value };
	}

	template<typename Type>
	Nullable<Type>& Nullable<Type>::operator = (const Type& value)
	{
		if (this->exists)
			*reinterpret_cast<Type*>(this->memory) = value;
		else
		{
			new(this->memory) Type{ value };
			this->exists = true;
		}

		return *this;
	}

	template<typename Type>
	Nullable<Type>::Nullable(Type&& value) :
		exists{ true }
	{
		new(this->memory) Type{ std::move(value) };
	}

	template<typename Type>
	Nullable<Type>& Nullable<Type>::operator = (Type&& value)
	{
		if (this->exists)
			*reinterpret_cast<Type*>(this->memory) = std::move(value);
		else
		{
			new(this->memory) Type{ std::move(value) };
			this->exists = true;
		}

		return *this;
	}

	template<typename Type>
	Nullable<Type>::Nullable(nullval_t) :
		exists{ false }
	{
	}

	template<typename Type>
	Nullable<Type>& Nullable<Type>::operator = (nullval_t)
	{
		if (this->exists)
		{
			Destruct(reinterpret_cast<Type*>(this->memory));
			this->exists = false;
		}

		return *this;
	}

	template<typename Type>
	Nullable<Type>::Nullable(const Nullable<Type>& other) :
		exists{ other.exists }
	{
		if (other.exists)
			new(this->memory) Type{ *reinterpret_cast<const Type*>(other.memory) };
	}

	template<typename Type>
	Nullable<Type>& Nullable<Type>::operator = (const Nullable<Type>& other)
	{
		if (this->exists)
		{
			if (other.exists)
			{
				*reinterpret_cast<Type*>(this->memory) = *reinterpret_cast<const Type*>(other.memory);
			}
			else
			{
				Destruct(reinterpret_cast<Type*>(this->memory));
				this->exists = false;
			}
		}
		else
		{
			if (other.exists)
			{
				new(this->memory) Type{ *reinterpret_cast<const Type*>(other.memory) };
				this->exists = true;
			}
		}

		return *this;
	}

	template<typename Type>
	Nullable<Type>::Nullable(Nullable<Type>&& other) :
		exists{ other.exists }
	{
		if (other.exists)
			new(this->memory) Type{ std::move(*reinterpret_cast<Type*>(other.memory)) };
	}

	template<typename Type>
	Nullable<Type>& Nullable<Type>::operator = (Nullable<Type>&& other)
	{
		if (this->exists)
		{
			if (other.exists)
			{
				*reinterpret_cast<Type*>(this->memory) = std::move(*reinterpret_cast<const Type*>(other.memory));
			}
			else
			{
				Destruct(reinterpret_cast<Type*>(this->memory));
				this->exists = false;
			}
		}
		else
		{
			if (other.exists)
			{
				new(this->memory) Type{ std::move(*reinterpret_cast<const Type*>(other.memory)) };
				this->exists = true;
			}
		}

		return *this;
	}

	template<typename Type>
	Nullable<Type>::~Nullable()
	{
		if (this->exists)
			Destruct(reinterpret_cast<Type*>(this->memory));
	}

	template<typename Type>
	Type* Nullable<Type>::operator -> ()
	{
		if (!this->exists)
			throw NullValueException{};

		return reinterpret_cast<Type*>(this->memory);
	}

	template<typename Type>
	Type& Nullable<Type>::operator *()
	{
		if (!this->exists)
			throw NullValueException{};

		return *reinterpret_cast<Type*>(this->memory);
	}

	template<typename Type>
	const Type* Nullable<Type>::operator -> () const
	{
		if (!this->exists)
			throw NullValueException{};

		return reinterpret_cast<const Type*>(this->memory);
	}

	template<typename Type>
	const Type& Nullable<Type>::operator *() const
	{
		if (!this->exists)
			throw NullValueException{};

		return *reinterpret_cast<const Type*>(this->memory);
	}

	template<typename Type>
	bool Nullable<Type>::operator == (nullval_t) const
	{
		return !this->exists;
	}

	template<typename Type>
	bool Nullable<Type>::operator != (nullval_t) const
	{
		return this->exists;
	}

	template<typename Type>
	bool Nullable<Type>::operator == (const Type& other) const
	{
		if (!this->exists)
			return false;

		return *reinterpret_cast<const Type*>(this->memory) == other;
	}

	template<typename Type>
	bool Nullable<Type>::operator != (const Type& other) const
	{
		if (!this->exists)
			return true;

		return *reinterpret_cast<const Type*>(this->memory) != other;
	}

	template<typename Type>
	Nullable<Type>::operator Type&()
	{
		if (!this->exists)
			throw NullValueException{};

		return *reinterpret_cast<Type*>(this->memory);
	}

	template<typename Type>
	Nullable<Type>::operator const Type&() const
	{
		if (!this->exists)
			throw NullValueException{};

		return *reinterpret_cast<const Type*>(this->memory);
	}
}