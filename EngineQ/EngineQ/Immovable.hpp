#ifndef ENGINEQ_IMMOVABLE_H
#define ENGINEQ_IMMOVABLE_H

class Immovable
{
public:
	Immovable() = default;
	Immovable(const Immovable&) = delete;
	Immovable(Immovable&&) = delete;
	Immovable& operator = (const Immovable&) = delete;
	Immovable& operator = (Immovable&&) = delete;
};

#endif // !ENGINEQ_IMMOVABLE_H
