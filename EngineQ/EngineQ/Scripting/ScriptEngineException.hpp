#ifndef ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_HPP
#define ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_HPP

#include <stdexcept>

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngineException : public std::runtime_error
		{
		public:
			ScriptEngineException(const char* message);
			ScriptEngineException(const std::string& message);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_HPP
