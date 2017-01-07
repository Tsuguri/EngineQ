#ifndef ENGINEQ_PROFILER_HPP
#define ENGINEQ_PROFILER_HPP

// Standard includes
#include <chrono>
#include <map>
#include <string>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"


namespace EngineQ
{
	class Profiler : Utilities::Immovable
	{
	private:
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		using Nanoseconds = std::chrono::nanoseconds;
		using Milliseconds = std::chrono::duration<double, std::milli>;
		using Seconds = std::chrono::duration<double>;
		using Clock = std::chrono::high_resolution_clock;

		class ProfilingInfo
		{
		private:
			TimePoint startTime;
			TimePoint endTime;
			Nanoseconds duration;

			Nanoseconds accumulator = Nanoseconds::zero();
			std::uint64_t iterations = 0;
			Nanoseconds minTime = Nanoseconds::max();
			Nanoseconds maxTime = Nanoseconds::min();

		public:
			void SetStart(TimePoint startTime);
			void SetEnd(TimePoint endTime);
			void Reset();

			std::uint64_t GetIterations() const;
			Milliseconds GetLastTime() const;
			Milliseconds GetMinTime() const;
			Milliseconds GetMaxTime() const;
			Milliseconds GetAverageTime() const;
		};

	private:
		std::map<std::string, ProfilingInfo> info;

		TimePoint lastTime = Clock::now();
		Seconds updateTime = Seconds(2);
		Seconds accumulator = Nanoseconds::zero();

		void Print() const;
		void Reset();
	
	public:
		void Start(const char* key);
		void Start(const std::string& key);
		void End(const char* key);
		void End(const std::string& key);
		void Update();
	};
}

#endif // !ENGINEQ_PROFILER_HPP
