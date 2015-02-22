#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <iostream>
#include <string>
#include <vector>
#include "timer.h"

using namespace std;

class Profiler
{
public:
	static void StartProfile(string a_ssName);
	static void EndProfile(string a_ssName);

private:

	//Extended Timer to have an attributed name
	class ExTimer : public timer
	{
	public:
		ExTimer()
		{}
		ExTimer(string a_ssName)
		{
			QueryPerformanceCounter(&current);
			QueryPerformanceCounter(&timeAtStart);
			m_ssName = a_ssName;
		}
		std::string m_ssName;
	};

	vector<ExTimer*> m_aoTimers;
	
	static Profiler* m_pSelf;
	Profiler() {};
	~Profiler() {};
};



#endif