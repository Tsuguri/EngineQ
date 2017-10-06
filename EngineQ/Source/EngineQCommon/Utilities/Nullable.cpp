#include "Nullable.hpp"


namespace Utilities
{
	NullValueException::NullValueException()
		: std::runtime_error("Attempt to access null value")
	{
	}
}