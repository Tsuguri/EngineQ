#include "Profiler.hpp"

// This project
#include "Logger.hpp"


namespace EngineQ
{
	void Profiler::ProfilingInfo::SetStart(TimePoint startTime)
	{
		this->startTime = startTime;
	}

	void Profiler::ProfilingInfo::SetEnd(TimePoint endTime)
	{
		this->endTime = endTime;
		this->duration = this->endTime - this->startTime;

		this->accumulator += this->duration;
		this->iterations += 1;

		if (this->minTime > this->duration)
			this->minTime = this->duration;

		if (this->maxTime < this->duration)
			this->maxTime = this->duration;
	}

	void Profiler::ProfilingInfo::Reset()
	{
		this->accumulator = Nanoseconds::zero();
		this->iterations = 0;

		this->minTime = Nanoseconds::max();
		this->maxTime = Nanoseconds::min();
	}

	std::uint64_t Profiler::ProfilingInfo::GetIterations() const
	{
		return this->iterations;
	}

	Profiler::Milliseconds Profiler::ProfilingInfo::GetLastTime() const
	{
		return this->duration;
	}

	Profiler::Milliseconds Profiler::ProfilingInfo::GetMinTime() const
	{
		return this->minTime;
	}

	Profiler::Milliseconds Profiler::ProfilingInfo::GetMaxTime() const
	{
		return this->maxTime;
	}

	Profiler::Milliseconds Profiler::ProfilingInfo::GetAverageTime() const
	{
		return std::chrono::duration_cast<Milliseconds>(this->accumulator) / this->iterations;
	}

	void Profiler::Start(const char * key)
	{
		this->Start(std::string(key));
	}

	void Profiler::Start(const std::string & key)
	{
		auto& info = this->info[key];

		info.SetStart(Clock::now());
	}

	void Profiler::End(const char * key)
	{
		this->End(std::string(key));
	}

	void Profiler::End(const std::string & key)
	{
		auto time = Clock::now();
		auto& info = this->info.at(key);

		info.SetEnd(time);
	}

	void Profiler::Update()
	{
		auto time = Clock::now();
		accumulator += time - lastTime;
		lastTime = time;

		if (accumulator >= updateTime)
		{
			accumulator = Seconds::zero();

			Print();
			Reset();
		}
	}

	void Profiler::Print() const
	{
		Logger::LogMessage("================================================== Profiler ==================================================\n");
		for (const auto& info : this->info)
		{
			Logger::LogMessage("\t-", info.first, ": \tAvg: ", info.second.GetAverageTime().count(), "ms \tMin: ", info.second.GetMinTime().count(), "ms \tMax: ", info.second.GetMaxTime().count(), "ms\n");
		}
		Logger::LogMessage("==============================================================================================================\n");
	}

	void Profiler::Reset()
	{
		for (auto it = this->info.begin(); it != this->info.end();)
		{
			if (it->second.GetIterations() == 0)
			{
				it = this->info.erase(it);
			}
			else
			{
				it->second.Reset();
				++it;
			}
		}
	}
}