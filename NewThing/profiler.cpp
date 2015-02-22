#include "profiler.h"

Profiler* Profiler::m_pSelf = nullptr;

void Profiler::StartProfile(string a_ssName)
{
	if (m_pSelf == nullptr)
	{
		m_pSelf = new Profiler();
	}
	
	if (m_pSelf->m_aoTimers.size() == 0)
	{
		m_pSelf->m_aoTimers.push_back(new ExTimer(a_ssName));
		cout << "Profile " << a_ssName << " has Started." << endl;
		return;
	}

	for (int i = 0; i < (int)m_pSelf->m_aoTimers.size(); i++)
	{
		if (a_ssName == m_pSelf->m_aoTimers[i]->m_ssName)
		{
			cout << "Profile " << a_ssName << " has already Started." << endl;
			return;
		}
	}
	
	m_pSelf->m_aoTimers.push_back(new ExTimer(a_ssName));
	cout << "Profile " << a_ssName << " has Started." << endl;
}

void Profiler::EndProfile(string a_ssName)
{
	if (m_pSelf != nullptr)
	{
		for (int i = 0; i < (int)m_pSelf->m_aoTimers.size(); i++)
		{
			if (a_ssName == m_pSelf->m_aoTimers[i]->m_ssName)
			{
				m_pSelf->m_aoTimers[i]->Update();
				cout << "Profile " << a_ssName << " has been stopped." << endl;
				cout << a_ssName << " has taken " << m_pSelf->m_aoTimers[i]->GetTimeSinceStart() << " to complete." << endl;
				delete m_pSelf->m_aoTimers[i];
				m_pSelf->m_aoTimers.erase(m_pSelf->m_aoTimers.begin() + i);
				return;
			}
		}
		cout << "Profile " << a_ssName << " does not exist";
		if (m_pSelf->m_aoTimers.size() == 0)
		{
			delete m_pSelf;
			m_pSelf = nullptr;
		}
	}
	else
		cout << "No Profile's have been initialised";
}
