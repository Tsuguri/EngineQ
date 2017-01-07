#include "Profiler.hpp"

// This project
#include "Logger.hpp"


namespace EngineQ
{
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

	bool Profiler::ProfilingInfo::IsActive() const
	{
		return this->isActive;
	}

	void Profiler::ProfilingInfo::Reset()
	{
		this->accumulator = Nanoseconds::zero();
		this->iterations = 0;

		this->minTime = Nanoseconds::max();
		this->maxTime = Nanoseconds::min();
		this->isActive = false;
	}
	


	void Profiler::CPUProfilingInfo::SetStart(TimePoint startTime)
	{
		this->isActive = true;
		this->startTime = startTime;
	}

	void Profiler::CPUProfilingInfo::SetEnd(TimePoint endTime)
	{
		this->endTime = endTime;
	}

	void Profiler::CPUProfilingInfo::Resolve()
	{
		this->duration = this->endTime - this->startTime;

		this->accumulator += this->duration;
		this->iterations += 1;

		if (this->minTime > this->duration)
			this->minTime = this->duration;

		if (this->maxTime < this->duration)
			this->maxTime = this->duration;
	}



	Profiler::GPUProfilingInfo::GPUProfilingInfo()
	{
		glGenQueries(2, querries.data());
	}

	Profiler::GPUProfilingInfo::GPUProfilingInfo(GPUProfilingInfo && other) :
		querries(other.querries)
	{
		other.querries = { 0, 0 };
	}

	Profiler::GPUProfilingInfo& Profiler::GPUProfilingInfo::operator = (GPUProfilingInfo&& other)
	{
		this->querries.swap(other.querries);
		return *this;
	}

	Profiler::GPUProfilingInfo::~GPUProfilingInfo()
	{
		glDeleteQueries(2, querries.data());
	}

	void Profiler::GPUProfilingInfo::Start()
	{
		this->isActive = true;
		glQueryCounter(querries[0], GL_TIMESTAMP);
	}

	void Profiler::GPUProfilingInfo::End()
	{
		glQueryCounter(querries[1], GL_TIMESTAMP);
	}

	void Profiler::GPUProfilingInfo::Resolve()
	{
		GLint64 startTime;
		glGetQueryObjecti64v(querries[0], GL_QUERY_RESULT, &startTime);
		GLint64 endTime;
		glGetQueryObjecti64v(querries[1], GL_QUERY_RESULT, &endTime);

		this->duration = Nanoseconds(endTime) - Nanoseconds(startTime);

		this->accumulator += this->duration;
		this->iterations += 1;

		if (this->minTime > this->duration)
			this->minTime = this->duration;

		if (this->maxTime < this->duration)
			this->maxTime = this->duration;
	}



	void Profiler::StartCPU(const char* key, const char* category)
	{
		this->StartCPU(std::string(key), std::string(category));
	}

	void Profiler::StartCPU(const std::string& key, const std::string& category)
	{
		auto& info = this->cpuInfo[category][key];

		info.SetStart(Clock::now());
	}

	void Profiler::EndCPU(const char* key, const char* category)
	{
		this->EndCPU(std::string(key), std::string(category));
	}

	void Profiler::EndCPU(const std::string& key, const std::string& category)
	{
		auto time = Clock::now();
		auto& info = this->cpuInfo.at(category).at(key);

		info.SetEnd(time);
	}


	void Profiler::StartGPU(const char* key, const char* category)
	{
		this->StartGPU(std::string(key), std::string(category));
	}

	void Profiler::StartGPU(const std::string& key, const std::string& category)
	{
		auto& info = this->gpuInfo[category][key];

		info.Start();
	}

	void Profiler::EndGPU(const char* key, const char* category)
	{
		this->EndGPU(std::string(key), std::string(category));
	}

	void Profiler::EndGPU(const std::string& key, const std::string& category)
	{
		auto& info = this->gpuInfo.at(category).at(key);
		
		info.End();
	}

	void Profiler::Update()
	{
		this->Resolve(this->cpuInfo);
		this->Resolve(this->gpuInfo);

		auto time = Clock::now();
		accumulator += time - lastTime;
		lastTime = time;

		if (accumulator >= updateTime)
		{
			accumulator = Seconds::zero();

			Logger::LogMessage("================================================== Profiler ==================================================\n");
			
			Logger::LogMessage("  CPU\n");
			this->Print(this->cpuInfo);
			
			Logger::LogMessage("  GPU\n");
			this->Print(this->gpuInfo);

			Logger::LogMessage("==============================================================================================================\n");

			this->Reset(this->cpuInfo);
			this->Reset(this->gpuInfo);
		}
	}
}