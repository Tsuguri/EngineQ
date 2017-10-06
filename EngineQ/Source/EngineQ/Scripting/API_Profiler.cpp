#include "API_Profiler.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Profiler::API_GetPrintInfo(bool& value)
		{
			value = Engine::Get().GetProfiler().GetPrintInfo();
		}

		void API_Profiler::API_SetPrintInfo(bool value)
		{
			Engine::Get().GetProfiler().SetPrintInfo(value);
		}

		void API_Profiler::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Profiler::API_GetPrintInfo", API_GetPrintInfo);
			scriptEngine.API_Register("EngineQ.Profiler::API_SetPrintInfo", API_SetPrintInfo);
		}
	}
}
