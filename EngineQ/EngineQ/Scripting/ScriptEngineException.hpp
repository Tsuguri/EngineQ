#ifndef ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_H
#define ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_H

#include <stdexcept>

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngineException : public std::runtime_error
		{
		public:
			ScriptEngineException(const char* message);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_SCRIPT_ENGINE_EXCEPTION_H
