#ifndef UTILITIES_ENUM_HELPERS_HPP
#define UTILITIES_ENUM_HELPERS_HPP

// Standard includes
#include <type_traits>

// This project
#include "Metaprogramming.hpp"


namespace Utilities
{
	template<typename TEnumType>
	constexpr bool IsFlagSet(TEnumType value, TEnumType flag)
	{
		using Type = typename std::underlying_type<TEnumType>::type;

		return static_cast<TEnumType>(static_cast<Type>(value) & static_cast<Type>(flag)) == flag;
	}

	template<typename TEnumType>
	constexpr TEnumType MakeFlags(TEnumType flag)
	{
		return flag;
	}

	template<typename TEnumType, typename... TEnumTypes>
	constexpr typename std::enable_if<Meta::AreAllSame<TEnumType, TEnumTypes...>::value, TEnumType>::type MakeFlags(TEnumType flag, TEnumTypes... flags)
	{
		using Type = typename std::underlying_type<TEnumType>::type;
		
		return static_cast<TEnumType>(static_cast<Type>(flag) | static_cast<Type>(MakeFlags(flags...)));
	}
}

/*
template<typename TEnumType, typename std::enable_if<std::is_enum<TEnumType>::value>::type = 0>
constexpr TEnumType operator | (TEnumType left, TEnumType right)
{
	using Type = typename std::underlying_type<TEnumType>::type;

	return static_cast<TEnumType>(static_cast<Type>(left) | static_cast<Type>(right));
}

template<typename TEnumType, typename std::enable_if<std::is_enum<TEnumType>::value>::type = 0>
constexpr TEnumType operator | (TEnumType left, TEnumType right)
{
	using Type = typename std::underlying_type<TEnumType>::type;

	return static_cast<TEnumType>(static_cast<Type>(left) & static_cast<Type>(right));
}
*/

#endif // !ENGINEQ_UTILITIES_ENUM_HELPERS_HPP
