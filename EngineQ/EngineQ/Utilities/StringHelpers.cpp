#include "StringHelpers.hpp"

namespace EngineQ
{
	namespace Utilities
	{
		template<>
		std::string ToString(const char& value)
		{
			return std::string(1, value);
		}

		template<>
		std::string ToString(const float& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const double& value)
		{
			return std::to_string(value);
		}


		template<>
		std::string ToString(const std::uint8_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::int8_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::uint16_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::int16_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::uint32_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::int32_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::uint64_t& value)
		{
			return std::to_string(value);
		}

		template<>
		std::string ToString(const std::int64_t& value)
		{
			return std::to_string(value);
		}
	}
}