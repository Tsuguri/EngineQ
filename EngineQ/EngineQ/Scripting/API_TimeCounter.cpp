#include "API_TimeCounter.hpp"

#include "ScriptEngine.hpp"

#include "../TimeCounter.hpp"

void EngineQ::Scripting::API_TimeCounter::API_GetTimeFromStart(float& time)
{
	time = TimeCounter::Get()->TimeFromStart();
}

void EngineQ::Scripting::API_TimeCounter::API_GetDeltaTime(float& time)
{
	time = TimeCounter::Get()->DeltaTime();
}

void EngineQ::Scripting::API_TimeCounter::API_Register(ScriptEngine& scriptEngine)
{
	scriptEngine.API_Register("EngineQ.Time::API_GetTimeFromStart", API_GetTimeFromStart);
	scriptEngine.API_Register("EngineQ.Time::API_GetDeltaTime", API_GetDeltaTime);
}
