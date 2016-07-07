#include "Nullable.hpp"

namespace EngineQ
{
	namespace Utilities
	{
		NullValueException::NullValueException()
			: std::runtime_error("Attempt to access null value")
		{
		}
	}
}