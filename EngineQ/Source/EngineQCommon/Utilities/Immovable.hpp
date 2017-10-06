#ifndef UTILITIES_IMMOVABLE_HPP
#define UTILITIES_IMMOVABLE_HPP


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

#endif // !UTILITIES_IMMOVABLE_HPP
