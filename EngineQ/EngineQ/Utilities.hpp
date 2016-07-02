#ifndef ENGINEQ_UTILITIES_H
#define ENGINEQ_UTILITIES_H

#include <string>

namespace EngineQ
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

#include "Utilities.inl"

#endif // !ENGINEQ_UTILITIES_H
