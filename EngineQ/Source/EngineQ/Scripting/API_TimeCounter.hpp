#ifndef ENGINEQ_SCRIPTING_API_TIMECOUNTER_HPP
#define ENGINEQ_SCRIPTING_API_TIMECOUNTER_HPP

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_TimeCounter
		{
		public:
			static void API_GetMillisecondsFromStart(std::uint64_t& time);
			static void API_GetDeltaTime(float& time);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif