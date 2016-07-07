#ifndef ENGINEQ_UTILITIES_IMMOVABLE_HPP
#define ENGINEQ_UTILITIES_IMMOVABLE_HPP

namespace EngineQ
{
	namespace Utilities
	{
		class Immovable
		{
		public:
			Immovable() = default;
			Immovable(const Immovable&) = delete;
			Immovable(Immovable&&) = delete;
			Immovable& operator = (const Immovable&) = delete;
			Immovable& operator = (Immovable&&) = delete;
		};
	}
}

#endif // !ENGINEQ_UTILITIES_IMMOVABLE_HPP
