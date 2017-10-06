#ifndef ENGINEQ_SCRIPTING_API_PROFILER_HPP
#define ENGINEQ_SCRIPTING_API_PROFILER_HPP

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;

		class API_Profiler
		{
		public:
			static void API_GetPrintInfo(bool& value);
			static void API_SetPrintInfo(bool value);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // ENGINEQ_SCRIPTING_API_PROFILER