#include "ScriptEngineException.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		ScriptEngineException::ScriptEngineException(const char* message)
			: std::runtime_error(message)
		{

		}
	}
}