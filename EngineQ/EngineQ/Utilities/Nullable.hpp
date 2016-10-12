#ifndef UTILITIES_NULLABLE_HPP
#define UTILITIES_NULLABLE_HPP

#include <stdexcept>

namespace Utilities
{
	class NullValueException final : public std::runtime_error
	{
	public:
		NullValueException();
	};

	struct nullval_t final
	{
	};

	template<typename Type>
	class Nullable
	{
	private:
		char memory[sizeof(Type)];
		bool exists;

		static void Destruct(Type* ptr);

	public:
		Nullable();

		Nullable(const Type& value);
		Nullable<Type>& operator = (const Type& value);

		Nullable(Type&& value);
		Nullable<Type>& operator = (Type&& value);

		Nullable(nullval_t);
		Nullable<Type>& operator = (nullval_t);

		Nullable(const Nullable<Type>& other);
		Nullable<Type>& operator = (const Nullable<Type>& other);

		Nullable(Nullable<Type>&& other);
		Nullable<Type>& operator = (Nullable<Type>&& other);

		~Nullable();

		Type* operator -> ();
		Type& operator *();

		const Type* operator -> () const;
		const Type& operator *() const;

		bool operator == (nullval_t) const;
		bool operator != (nullval_t) const;
		bool operator == (const Type& other) const;
		bool operator != (const Type& other) const;

		explicit operator Type&();
		explicit const operator Type&() const;
	};
}

constexpr Utilities::nullval_t nullval{};

#include "Nullable.inl"

#endif // !UTILITIES_NULLABLE_HPP