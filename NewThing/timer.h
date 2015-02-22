#ifndef _TIMER_H_
#define _TIMER_H_
#include <Windows.h>

class timer
{
public:
	timer();

	void Update();
	float GetDeltaTime();
	float GetTimeSinceStart();

protected:
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	LARGE_INTEGER previous;
	LARGE_INTEGER timeAtStart;
};
#endif