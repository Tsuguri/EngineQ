#ifndef ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP
#define ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP

#include <string>
#include <sstream>

namespace EngineQ
{
	namespace Utilities
	{
		template<typename Type>
		std::string ToString(const Type& value);

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Type& value);

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Type& value);
	}
}

#include "StringHelpers.inl"

#endif // !ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP
