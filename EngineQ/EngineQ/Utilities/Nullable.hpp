#ifndef UTILITIES_NULLABLE_HPP
#define UTILITIES_NULLABLE_HPP

#include <stdexcept>
#include <type_traits>

namespace Utilities
{
	template<typename Type, bool>
	struct DestructHelper
	{
		static void Destruct(Type* ptr);
	};

	template<typename Type>
	struct DestructHelper<Type, true>
	{
		static void Destruct(Type* ptr);
	};

	class NullValueException : public std::runtime_error
	{
	public:
		NullValueException();
	};

	struct nullval_t
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

		bool operator == (nullval_t) const;
		bool operator != (nullval_t) const;
		bool operator == (const Type& other) const;
		bool operator != (const Type& other) const;

		explicit operator Type&() const;
		explicit operator Type&();
	};

	template<typename Type, typename ...Args>
	Nullable<Type> MakeNullable(Args&& ...args);

	template<typename Type>
	Nullable<Type> MakeNullableEmpty();
}

constexpr Utilities::nullval_t nullval{};

#include "Nullable.inl"

#endif // !UTILITIES_NULLABLE_HPP