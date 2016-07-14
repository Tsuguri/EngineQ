#ifndef ENGINEQ_SCRIPTING_API_TIMECOUNTER_HPP
#define ENGINEQ_SCRIPTING_API_TIMECOUNTER_HPP


#include "ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_TimeCounter
		{
		public:
			static void API_GetTimeFromStart(float& time);
			static void API_GetDeltaTime(float& time);
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif