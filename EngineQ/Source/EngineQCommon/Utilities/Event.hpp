#ifndef UTILITIES_EVENT_HPP
#define UTILITIES_EVENT_HPP

// Standard includes
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>


namespace Utilities
{
	template<typename TFunctor>
	class EventHandler;

	template<typename TReturn, typename... TArgs>
	class EventHandler<TReturn(TArgs...)>
	{
	private:
		std::function<TReturn(TArgs...)> function;
		std::shared_ptr<char> comparer = std::make_shared<char>();

	public:

		EventHandler(TReturn(*function)(TArgs...)) :
			function{ function }
		{
		}

		template<typename TFunctor, TReturn(TFunctor::*Op)(TArgs...) const = &TFunctor::operator()>
		EventHandler(const TFunctor& functor) :
			function{ functor }
		{
		}

		template<typename TType>
		EventHandler(TType& object, TReturn(TType::*method)(TArgs...)) :
			function{ [&object,method](TArgs... args) { return (object.*method)(args...); } }
		{
		}

		template<typename TType>
		EventHandler(TType& object, TReturn(TType::*method)(TArgs...) const) :
			function{ [&object,method](TArgs... args) { return (object.*method)(args...); } }
		{
		}

		template<typename TType>
		EventHandler(const TType& object, TReturn(TType::*method)(TArgs...) const) :
			function{ [&object,method](TArgs... args) { return (object.*method)(args...); } }
		{
		}

		template<typename TType>
		EventHandler(const TType&& object, TReturn(TType::*method)(TArgs...)) = delete;

		template<typename TType>
		EventHandler(const TType&& object, TReturn(TType::*method)(TArgs...) const) = delete;

		TReturn operator() (TArgs... args) const
		{
			return function(args...);
		}

		bool operator == (const EventHandler& other) const
		{
			return this->comparer.get() == other.comparer.get();
		}

		bool operator != (const EventHandler& other) const
		{
			return this->comparer.get() != other.comparer.get();
		}
	};

	class FunctionNotFoundException : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	class EmptyEventException : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	template<typename TParent, typename TFunctor>
	class Event;

	template<typename TParent, typename TReturn, typename... TArgs>
	class Event<TParent, TReturn(TArgs...)>
	{
		friend TParent;

	private:
		class
		{
			friend class Event;

		private:
			// Private

			std::vector<EventHandler<TReturn(TArgs...)>> functions;
		} impl;


		// Friend

		TReturn Invoke(TArgs... args) const
		{
			if (this->impl.functions.size() == 0)
				throw EmptyEventException{ "" };

			auto last = --this->impl.functions.end();
			for (auto it = this->impl.functions.begin(); it != last; ++it)
				(*it)(args...);

			return (*last)(args...);
		}

		void Clear()
		{
			this->impl.functions.clear();
		}

		bool IsEmpty()
		{
			return this->impl.functions.size() == 0;
		}

		Event& operator = (std::nullptr_t)
		{
			this->impl.functions.clear();
			return *this;
		}

		bool operator == (std::nullptr_t)
		{
			return this->impl.functions.size() == 0;
		}

		bool operator != (std::nullptr_t)
		{
			return this->impl.functions.size() != 0;
		}

	public:
		// Public

		Event& operator += (const EventHandler<TReturn(TArgs...)>& function)
		{
			this->impl.functions.push_back(function);
			return *this;
		}

		Event& operator -= (const EventHandler<TReturn(TArgs...)>& function)
		{
			auto it = std::find(this->impl.functions.begin(), this->impl.functions.end(), function);

			if (it == this->impl.functions.end())
				throw FunctionNotFoundException{ "" };

			this->impl.functions.erase(it);
			return *this;
		}

		Event& operator -= (const EventHandler<TReturn(TArgs...)>&&) = delete;
	};

	/*
	template<typename... TArgs>
	using Action = void(TArgs...);

	template<typename TReturn, typename... TArgs>
	using Function = TReturn(TArgs...);

	template<typename... TArgs>
	using Predicate = bool(TArgs...);
	*/
}

#endif // !UTILITIES_EVENT_HPP