#ifndef ENGINEQ_TIMECOUNTER_HPP
#define ENGINEQ_TIMECOUNTER_HPP


class TimeCounter
{
	static TimeCounter* instance;
	float timeFromStart=0;
	float deltaTime=0;

public:
	float TimeFromStart();
	float DeltaTime();
	void Update(float time, float deltaTime);
	static TimeCounter* Get();
};

#endif
