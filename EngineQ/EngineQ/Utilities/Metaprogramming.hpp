#ifndef UTILITIES_METAPROGRAMMING_HPP
#define UTILITIES_METAPROGRAMMING_HPP

#include <cstddef>

namespace Meta
{
	template<typename TType, typename... TTypes>
	struct ContainsType;

	template<typename TType, typename... TTypes>
	struct ContainsType<TType, TType, TTypes...>
	{
		static constexpr bool value = true;
	};

	template<typename TType, typename THead, typename... TTail>
	struct ContainsType<TType, THead, TTail...>
	{
		static constexpr bool value = ContainsType<TType, TTail...>::value;
	};

	template<typename TType>
	struct ContainsType<TType>
	{
		static constexpr bool value = false;
	};



	template<typename TType, TType VValue, TType... VValues>
	struct ContainsValue;

	template<typename TType, TType VValue, TType... VValues>
	struct ContainsValue<TType, VValue, VValue, VValues...>
	{
		static constexpr bool value = true;
	};

	template<typename TType, TType VValue, TType VHead, TType... VTail>
	struct ContainsValue<TType, VValue, VHead, VTail...>
	{
		static constexpr bool value = ContainsValue<TType, VValue, VTail...>::value;
	};

	template<typename TType, TType VValue>
	struct ContainsValue<TType, VValue>
	{
		static constexpr bool value = false;
	};



	template<typename TFirst, typename... TRest>
	struct HasDuplicateTypes
	{
		static constexpr bool value = ContainsType<TFirst, TRest...>::value || HasDuplicateTypes<TRest...>::value;
	};

	template<typename TLast>
	struct HasDuplicateTypes<TLast>
	{
		static constexpr bool value = false;
	};



	template<typename TType, TType VFirst, TType... VRest>
	struct HasDuplicateValues
	{
		static constexpr bool value = ContainsValue<TType, VFirst, VRest...>::value || HasDuplicateValues<TType, VRest...>::value;
	};

	template<typename TType, TType VLast>
	struct HasDuplicateValues<TType, VLast>
	{
		static constexpr bool value = false;
	};




	template<typename TType, typename... TTypes>
	struct TypeIndex;

	template<typename TType, typename... TTypes>
	struct TypeIndex<TType, TType, TTypes...>
	{
		static_assert(!ContainsType<TType, TTypes...>::value, "List contains multiple type");

		static constexpr std::size_t value = 0;
	};

	template<typename TType, typename THead, typename... TRest>
	struct TypeIndex<TType, THead, TRest...>
	{
		static constexpr std::size_t value = 1 + TypeIndex<TType, TRest...>::value;
	};

	template<typename TType>
	struct TypeIndex<TType>
	{
		static_assert(sizeof(TType) == 0, "Element not found");

		static constexpr std::size_t value = 0;
	};


	constexpr std::size_t Max(std::size_t val1, std::size_t val2)
	{
		return val1 > val2 ? val1 : val2;
	}

	template<typename TType, typename... TTypes>
	struct MaxTypeSize
	{
		static constexpr std::size_t value = Max(sizeof(TType), MaxTypeSize<TTypes...>::value);
	};

	template<typename TType>
	struct MaxTypeSize<TType>
	{
		static constexpr std::size_t value = sizeof(TType);
	};


	template<std::size_t TElements, typename TType, TType... TValues>
	struct SumN;

	template<std::size_t TElements, typename TType, TType THead, TType... TTail>
	struct SumN<TElements, TType, THead, TTail...>
	{
		static constexpr TType value = THead + SumN<TElements - 1, TType, TTail...>::value;
	};

	template<typename TType, TType THead, TType... TTail>
	struct SumN<0, TType, THead, TTail...>
	{
		static constexpr TType value = 0;
	};

	template<typename TType, TType... TValues>
	struct SumN<0, TType, TValues...>
	{
		static constexpr TType value = 0;
	};

	template<typename TType>
	struct SumN<0, TType>
	{
		static constexpr TType value = 0;
	};

	template<std::size_t TElements, typename TType>
	struct SumN<TElements, TType>
	{
		static_assert(sizeof(TType) == 0, "Not enough values to sum");
	};




	template<typename TFunction, TFunction THead, TFunction... TTail>
	struct Invoker
	{
		template<typename... TArgs>
		inline static void Invoke(TArgs&&... args)
		{
			THead(std::forward<TArgs>(args)...);
			Invoker<TFunction, TTail...>::Invoke(std::forward<TArgs>(args)...);
		}
	};

	template<typename TFunction, TFunction TLast>
	struct Invoker<TFunction, TLast>
	{
		template<typename... TArgs>
		inline static void Invoke(TArgs&&... args)
		{
			TLast(std::forward<TArgs>(args)...);
		}
	};



	template<template<typename> class TConcept, typename THead, typename... TTail>
	struct SatisfyConcept
	{
		static constexpr bool value = TConcept<THead>::value && SatisfyConcept<TConcept, TTail...>::value;
	};

	template<template<typename> class TConcept, typename TLast>
	struct SatisfyConcept<TConcept, TLast>
	{
		static constexpr bool value = TConcept<TLast>::value;
	};



	template<typename THead, typename... TTail>
	struct AreAllSame;

	template<typename TType, typename... TRest>
	struct AreAllSame<TType, TType, TRest...>
	{
		static constexpr bool value = AreAllSame<TType, TRest...>::value;
	};

	template<typename TFirst, typename TSecond, typename... TRest>
	struct AreAllSame<TFirst, TSecond, TRest...>
	{
		static constexpr bool value = false;
	};

	template<typename TTail>
	struct AreAllSame<TTail>
	{
		static constexpr bool value = true;
	};







	template<bool VValue1, bool VValue2>
	struct CombineAnd
	{
		static constexpr bool value = VValue1 && VValue2;
	};

	template<bool VValue1, bool VValue2>
	struct CombineOr
	{
		static constexpr bool value = VValue1 || VValue2;
	};

	template<template<bool, bool> class TCombineType, template<typename, typename...> class THead, template<typename, typename...> class... TTail>
	struct CombinedConcept
	{
		template<typename TType>
		using type = TCombineType<THead<TType>::value, CombinedConcept<TCombineType, TTail...>::template type<TType>::value>;
	};

	template<template<bool, bool> class TCombineType, template<typename, typename...> class TLast>
	struct CombinedConcept<TCombineType, TLast>
	{
		template<typename TType>
		using type = TLast<TType>;
	};
}

#endif // !UTILITIES_METAPROGRAMMING_HPP
