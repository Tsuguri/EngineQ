#ifndef ENGINEQ_SCRIPTING_SCRIPTING_EXCEPTIONS_HPP
#define ENGINEQ_SCRIPTING_SCRIPTING_EXCEPTIONS_HPP

// Standard includes
#include <stdexcept>


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngineException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_SCRIPTING_EXCEPTIONS_HPP
