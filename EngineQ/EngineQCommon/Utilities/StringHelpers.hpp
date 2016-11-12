#ifndef UTILITIES_STRING_HPPELPERS_HPP
#define UTILITIES_STRING_HPPELPERS_HPP

#include <string>
#include <sstream>

namespace Utilities
{
	template<typename Type>
	std::string ToString(const Type& value);

	template<typename Type>
	std::istream& operator >>= (std::istream& stream, Type& value);

	template<typename Type>
	std::ostream& operator <<= (std::ostream& stream, const Type& value);

	constexpr bool IsDigit(char c)
	{
		return '0' <= c && c <= '9';
	}

	constexpr bool IsLetter(char c)
	{
		return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
	}

	constexpr bool IsNameFirstChar(char c)
	{
		return IsLetter(c) || c == '_';
	}

	constexpr bool IsNameChar(char c)
	{
		return IsNameFirstChar(c) || IsDigit(c);
	}
}

#include "StringHelpers.inl"

#endif // !UTILITIES_STRING_HPPELPERS_HPP
