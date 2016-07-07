#ifndef ENGINEQ_UTILITIES_UNCOPYABLE_HPP
#define ENGINEQ_UTILITIES_UNCOPYABLE_HPP

namespace EngineQ
{
	namespace Utilities
	{
		class Uncopyable
		{
		public:
			Uncopyable() = default;
			Uncopyable(const Uncopyable&) = delete;
			Uncopyable& operator = (const Uncopyable&) = delete;
		};
	}
}

#endif // !ENGINEQ_UTILITIES_UNCOPYABLE_HPP
