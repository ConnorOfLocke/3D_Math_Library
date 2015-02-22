#include "timer.h"

timer::timer()
{
	//PUTS THE CURRENT SYS TIME INTO 64 BIT VALUE
	QueryPerformanceCounter(&current);
	QueryPerformanceCounter(&timeAtStart);
}

void timer::Update()
{
	previous = current;
	QueryPerformanceCounter(&current);
	QueryPerformanceFrequency(&freq);
}

float timer::GetDeltaTime()
{
	return ((float)current.QuadPart - (float)previous.QuadPart) / (float)freq.QuadPart;
}

float timer::GetTimeSinceStart()
{
	return ((float)current.QuadPart - (float)timeAtStart.QuadPart) / (float)freq.QuadPart;
}
