#ifndef ENGINEQ_UTILITIES_NULLABLE_HPP
#define ENGINEQ_UTILITIES_NULLABLE_HPP

#include <stdexcept>

namespace EngineQ
{
	namespace Utilities
	{
		class NullValueException : public std::runtime_error
		{
		public:
			NullValueException();
		};

		struct nullval_t
		{
		};

		template<typename T>
		class Nullable
		{
		private:
			char memory[sizeof(T)];
			bool exists;

		public:
			Nullable();

			Nullable(const T& value);
			Nullable<T>& operator = (const T& value);

			Nullable(T&& value);
			Nullable<T>& operator = (T&& value);

			Nullable(nullval_t);
			Nullable<T>& operator = (nullval_t);

			Nullable(const Nullable<T>& other);
			Nullable<T>& operator = (const Nullable<T>& other);

			Nullable(Nullable<T>&& other);
			Nullable<T>& operator = (Nullable<T>&& other);

			~Nullable();

			T* operator -> ();
			T& operator *();

			bool operator == (nullval_t) const;
			bool operator != (nullval_t) const;
			bool operator == (const T& other) const;
			bool operator != (const T& other) const;

			explicit operator T&() const;
			explicit operator T&();
		};

		template<typename T, typename ...Args>
		Nullable<T> MakeNullable(Args&& ...args);

		template<typename T>
		Nullable<T> MakeNullableEmpty();
	}
}

constexpr EngineQ::Utilities::nullval_t nullval{};

#include "Nullable.inl"

#endif // !ENGINEQ_UTILITIES_NULLABLE_HPP