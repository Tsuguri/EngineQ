#include "TimeCounter.hpp"

namespace EngineQ
{
	void TimeCounter::Update()
	{
		auto time = Clock::now();
		this->deltaTime = time - this->lastTime;

		if (this->deltaTime > this->maxDeltaTime)
			this->deltaTime = this->maxDeltaTime;

		this->lastTime = time;
	}

	float TimeCounter::GetDeltaTime()
	{
		return this->deltaTime.count();
	}

	std::uint64_t TimeCounter::GetMillisecondsFromStart()
	{
		auto time = Clock::now();
		auto diff = time - this->startTime;

		return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
	}
}