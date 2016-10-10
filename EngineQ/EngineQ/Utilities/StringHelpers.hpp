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
}

#include "StringHelpers.inl"

#endif // !UTILITIES_STRING_HPPELPERS_HPP
