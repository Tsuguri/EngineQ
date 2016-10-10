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



	template<typename... TTypes>
	struct HasDuplicate;

	template<typename TFirst, typename... TRest>
	struct HasDuplicate<TFirst, TRest...>
	{
		static constexpr bool value = ContainsType<TFirst, TRest...>::value || HasDuplicate<TRest...>::value;
	};

	template<typename TLast>
	struct HasDuplicate<TLast>
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
}

#endif // !UTILITIES_METAPROGRAMMING_HPP
