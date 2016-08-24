#ifndef ENGINEQ_PROPERTY_HPP
#define ENGINEQ_PROPERTY_HPP

#include <cstddef>

namespace EngineQ
{
	namespace Experimental
	{
		// Offset property
		template<
			typename TType,
			std::size_t Offset,
			typename TFun1,
			TFun1 Fun1,
			typename TFun2 = void*,
			TFun2 Fun2 = nullptr
		>
			struct Property2;

		// Fun1: val Getter const
		// Fun2: const ref Setter
		template<
			typename TType,
			std::size_t Offset,
			typename TParent,
			TType(TParent::*Getter)() const,
			void(TParent::*Setter)(const TType&)
		>
			struct Property2<TType, Offset, TType(TParent::*)() const, Getter, void(TParent::*)(const TType&), Setter>
		{
			inline operator TType() const
			{
				return (reinterpret_cast<const TParent*>(this - Offset)->*Getter)();
			}

			inline TType operator = (const TType& value)
			{
				(reinterpret_cast<TParent*>(this - Offset)->*Setter)(value);
				return value;
			}
		};
	}



	template<typename TParent>
	class BaseProperty
	{
	private:
		const std::size_t offset;

	protected:
		inline const TParent* GetParent() const
		{
			return reinterpret_cast<const TParent*>(reinterpret_cast<const char*>(this) - offset);
		}

		inline TParent* GetParent()
		{
			return reinterpret_cast<TParent*>(reinterpret_cast<char*>(this) - offset);
		}

	public:
		constexpr BaseProperty(const TParent* parent) noexcept
			: offset{ static_cast<std::size_t>(reinterpret_cast<const char*>(this) - reinterpret_cast<const char*>(parent)) }
		{
		}

		/*
		constexpr BaseProperty(std::size_t offset) noexcept
		: offset{ offset }
		{
		}
		*/

		BaseProperty(const BaseProperty&) = default;
		BaseProperty(BaseProperty&&) = default;
		BaseProperty& operator = (const BaseProperty&) { return *this; }
		BaseProperty& operator = (BaseProperty&&) { return *this; }

		BaseProperty* operator&() = delete;

		void* operator new(std::size_t) = delete;
		void* operator new[](std::size_t) = delete;
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};


	template<
		typename TType,
		typename TFun1,
		TFun1 Fun1,
		typename TFun2 = void*,
		TFun2 Fun2 = nullptr
	>
		class Property;



	template<
		typename TType,
		TType(*Getter)()
	>
		class Property<TType, TType(*)(), Getter>
	{
	public:
		inline operator TType()
		{
			return (*Getter)();
		}
	};




#pragma region Getter

	// Fun1: val Getter
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)()
	>
		class Property<TType, TType(TParent::*)(), Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType()
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}
	};

	// Fun1: val Getter const
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)() const
	>
		class Property<TType, TType(TParent::*)() const, Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType() const
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}
	};

#pragma endregion

#pragma region Setter

	// Fun1: val Setter
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(TType)
	>
		class Property<TType, void(TParent::*)(TType), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline void operator = (TType value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
		}
	};

	// Fun1: const ref Setter
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(const TType&)
	>
		class Property<TType, void(TParent::*)(const TType&), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline void operator = (const TType& value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
		}
	};

#pragma endregion

#pragma region Getter & Setter

	// Fun1: val Getter
	// Fun2: const ref Setter
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)(),
		void(TParent::*Setter)(const TType&)
	>
		class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(const TType&), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType()
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (const TType& value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: val Getter const
	// Fun2: const ref Setter
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)() const,
		void(TParent::*Setter)(const TType&)
	>
		class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(const TType&), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType() const
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (const TType& value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: const ref Setter
	// Fun2: val Getter const
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(const TType&),
		TType(TParent::*Getter)() const
	>
		class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)() const, Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType() const
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (const TType& value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: const ref Setter
	// Fun2: val Getter
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(const TType&),
		TType(TParent::*Getter)()
	>
		class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)(), Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType()
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (const TType& value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: val Getter
	// Fun2: val Setter
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)(),
		void(TParent::*Setter)(TType)
	>
		class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(TType), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType()
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (TType value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: val Getter const
	// Fun2: val Setter
	template<
		typename TParent,
		typename TType,
		TType(TParent::*Getter)() const,
		void(TParent::*Setter)(TType)
	>
		class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(TType), Setter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType() const
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (TType value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: val Setter
	// Fun2: val Getter const
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(TType),
		TType(TParent::*Getter)() const
	>
		class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)() const, Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType() const
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (TType value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};

	// Fun1: val Setter
	// Fun2: val Getter
	template<
		typename TParent,
		typename TType,
		void(TParent::*Setter)(TType),
		TType(TParent::*Getter)()
	>
		class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)(), Getter> : protected BaseProperty<TParent>
	{
		using BaseProperty<TParent>::BaseProperty;

	public:
		inline operator TType()
		{
			return (BaseProperty<TParent>::GetParent()->*Getter)();
		}

		inline TType operator = (TType value)
		{
			(BaseProperty<TParent>::GetParent()->*Setter)(value);
			return value;
		}
	};
}

#define PropertyFunc(function) decltype(&function), &function

#pragma endregion

#endif // !ENGINEQ_PROPERTY_HPP