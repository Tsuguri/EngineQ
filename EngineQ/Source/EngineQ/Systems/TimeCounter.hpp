#ifndef ENGINEQ_TIMECOUNTER_HPP
#define ENGINEQ_TIMECOUNTER_HPP

// Standard includes
#include <memory>
#include <chrono>
#include <cstdint>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"


namespace EngineQ
{
	class TimeCounter : private Utilities::Immovable
	{
	private:
		using Clock = std::chrono::high_resolution_clock;

	private:
		Clock::time_point startTime = Clock::now();
		Clock::time_point lastTime = Clock::now();

		std::chrono::duration<float> maxDeltaTime = std::chrono::duration<float>(1.0f / 30.0f);
		std::chrono::duration<float> deltaTime = std::chrono::duration<float>::zero();

	public:
		void Update();
		float GetDeltaTime();
		std::uint64_t GetMillisecondsFromStart();
	};
}

#endif
