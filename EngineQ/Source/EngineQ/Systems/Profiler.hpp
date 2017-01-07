#ifndef ENGINEQ_PROFILER_HPP
#define ENGINEQ_PROFILER_HPP

// Standard includes
#include <chrono>
#include <map>
#include <string>
#include <array>
#include <iomanip>

// Libraries
#include <GL\glew.h>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"


namespace EngineQ
{
	class Profiler : Utilities::Immovable
	{
	private:
		using Nanoseconds = std::chrono::nanoseconds;
		using Milliseconds = std::chrono::duration<double, std::milli>;
		using Seconds = std::chrono::duration<double>;
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock, Nanoseconds>;

		class ProfilingInfo
		{
		protected:
			Nanoseconds duration = Nanoseconds::zero();

			Nanoseconds accumulator = Nanoseconds::zero();
			std::uint64_t iterations = 0;
			Nanoseconds minTime = Nanoseconds::max();
			Nanoseconds maxTime = Nanoseconds::min();

			bool isActive = false;

		public:
			std::uint64_t GetIterations() const;
			Milliseconds GetLastTime() const;
			Milliseconds GetMinTime() const;
			Milliseconds GetMaxTime() const;
			Milliseconds GetAverageTime() const;
			bool IsActive() const;

			void Reset();
		};

		class CPUProfilingInfo : public ProfilingInfo
		{
		private:
			TimePoint startTime;
			TimePoint endTime;

		public:
			void SetStart(TimePoint startTime);
			void SetEnd(TimePoint endTime);
			void Resolve();
		};

		class GPUProfilingInfo : public ProfilingInfo
		{
		private:
			std::array<GLuint, 2> querries;

		public:
			GPUProfilingInfo();
			~GPUProfilingInfo();
			GPUProfilingInfo(GPUProfilingInfo&& other);
			GPUProfilingInfo& operator = (GPUProfilingInfo&& other);

			GPUProfilingInfo(const GPUProfilingInfo&) = delete;
			GPUProfilingInfo& operator = (const GPUProfilingInfo&) = delete;
			
			void Start();
			void End();
			void Resolve();
		};

	private:
		std::map<std::string, std::map<std::string, CPUProfilingInfo>> cpuInfo;
		std::map<std::string, std::map<std::string, GPUProfilingInfo>> gpuInfo;

		TimePoint lastTime = Clock::now();
		Seconds updateTime = Seconds(5);
		Seconds accumulator = Nanoseconds::zero();

		template<typename TProfilingInfo>
		static void Resolve(std::map<std::string, std::map<std::string, TProfilingInfo>>& infoMap)
		{
			for (auto categoryIt = infoMap.begin(); categoryIt != infoMap.end();)
			{
				for (auto infoIt = categoryIt->second.begin(); infoIt != categoryIt->second.end();)
				{
					if (!infoIt->second.IsActive())
					{
						infoIt = categoryIt->second.erase(infoIt);
					}
					else
					{
						infoIt->second.Resolve();
						++infoIt;
					}
				}

				if (categoryIt->second.empty())
					categoryIt = infoMap.erase(categoryIt);
				else
					++categoryIt;
			}
		}

		template<typename TProfilingInfo>
		static void Reset(std::map<std::string, std::map<std::string, TProfilingInfo>>& infoMap)
		{
			for (auto& category : infoMap)
				for (auto& info : category.second)
					info.second.Reset();
		}

		template<typename TProfilingInfo>
		static void Print(std::map<std::string, std::map<std::string, TProfilingInfo>>& infoMap)
		{
			for (const auto& category : infoMap)
			{
				constexpr int Precision = 3;
				constexpr int Decimal = 3;
				constexpr int Width = Precision + 1 + Decimal;

				Logger::LogMessage("    ", category.first, "\n");
				for (const auto& info : category.second)
				{
					Logger::LogMessage("      ",
						std::setw(50), std::left, std::setfill('.'), info.first,
						std::right, std::fixed, std::setprecision(Precision), std::setfill(' '),
						" Avg: ", std::setw(Width), info.second.GetAverageTime().count(), " ms   Min: ", std::setw(Width), info.second.GetMinTime().count(), " ms   Max: ", std::setw(Width), info.second.GetMaxTime().count(), " ms\n");
				}
			}
		}

	public:
		void StartCPU(const char* key, const char* category);
		void StartCPU(const std::string& key, const std::string& category);
		void EndCPU(const char* key, const char* category);
		void EndCPU(const std::string& key, const std::string& category);
		void StartGPU(const char* key, const char* category);
		void StartGPU(const std::string& key, const std::string& category);
		void EndGPU(const char* key, const char* category);
		void EndGPU(const std::string& key, const std::string& category);
		
		void Update();
	};
}

#endif // !ENGINEQ_PROFILER_HPP
