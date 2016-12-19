#include "TimeCounter.hpp"


std::unique_ptr<TimeCounter> TimeCounter::instance = nullptr;

float TimeCounter::TimeFromStart()
{
	return timeFromStart;
}

float TimeCounter::DeltaTime()
{
	return deltaTime;
}

void TimeCounter::Update(float time, float deltaTime)
{
	this->deltaTime = deltaTime;
	this->timeFromStart = time;
}

TimeCounter& TimeCounter::Get()
{
	if (instance == nullptr)
		instance = std::make_unique<TimeCounter>();

	return *instance;
}
