#include "API_TimeCounter.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"
#include "EngineQ/Systems/TimeCounter.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_TimeCounter::API_GetMillisecondsFromStart(std::uint64_t& time)
		{
			time = Engine::Get().GetTimeCounter().GetMillisecondsFromStart();
		}

		void API_TimeCounter::API_GetDeltaTime(float& time)
		{
			time = Engine::Get().GetTimeCounter().GetDeltaTime();
		}

		void API_TimeCounter::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Time::API_GetMillisecondsFromStart", API_GetMillisecondsFromStart);
			scriptEngine.API_Register("EngineQ.Time::API_GetDeltaTime", API_GetDeltaTime);
		}
	}
}
