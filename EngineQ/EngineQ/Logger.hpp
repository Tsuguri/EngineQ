#ifndef ENGINEQ_LOGGER_HPP
#define ENGINEQ_LOGGER_HPP

// Standard includes
#include <iostream>


namespace EngineQ
{
	class Logger
	{
	public:
		template<typename TFirst, typename... TRest>
		static inline void LogMessage(const TFirst& first, const TRest&... rest)
		{
			std::cout << first;
			LogMessage(rest...);
		}

		template<typename TLast>
		static inline void LogMessage(const TLast& last)
		{
			std::cout << last;
		}
	};
}

#endif // !ENGINEQ_LOGGER_HPP
