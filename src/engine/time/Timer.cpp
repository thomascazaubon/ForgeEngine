#include "Timer.h"

namespace ForgeEngine
{
	void Timer::Start(float msDuration)
	{
		m_ElapsedTime = 0.f;
		m_Duration = msDuration;
		m_IsInitialized = true;
		m_IsStarted = true;
		m_IsElapsed = false;
	}

	void Timer::Stop()
	{
		m_IsInitialized = false;
		m_IsStarted = false;
		m_IsElapsed = false;
	}

	void Timer::Resume()
	{
		if (m_IsInitialized)
		{
			m_IsStarted = true;
		}
	}

	void Timer::Update(float dT)
	{
		if (m_IsStarted && !m_IsElapsed)
		{
			m_ElapsedTime += dT;
			if (m_ElapsedTime >= m_Duration)
			{
				m_IsElapsed = true;
			}
		}
	}
}