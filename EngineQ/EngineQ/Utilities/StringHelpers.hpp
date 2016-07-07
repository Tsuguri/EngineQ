#ifndef ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP
#define ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP

#include <string>

namespace EngineQ
{
	namespace Utilities
	{
		template<typename Type>
		std::string ToString(const Type& value);

		template<>
		std::string ToString(const char& value);

		template<>
		std::string ToString(const float& value);

		template<>
		std::string ToString(const double& value);

		template<>
		std::string ToString(const std::uint8_t& value);

		template<>
		std::string ToString(const std::int8_t& value);

		template<>
		std::string ToString(const std::uint16_t& value);

		template<>
		std::string ToString(const std::int16_t& value);

		template<>
		std::string ToString(const std::uint32_t& value);

		template<>
		std::string ToString(const std::int32_t& value);

		template<>
		std::string ToString(const std::uint64_t& value);

		template<>
		std::string ToString(const std::int64_t& value);
	}
}

#include "StringHelpers.inl"

#endif // !ENGINEQ_UTILITIES_STRING_HPPELPERS_HPP
