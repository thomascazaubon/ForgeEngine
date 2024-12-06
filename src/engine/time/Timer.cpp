#include "Timer.h"

#include "engine/debug/Assert.h"
#include "engine/math/MathUtils.h"
#include "engine/render/OpenGL.h"

#include <format>

namespace ForgeEngine
{
	void Timer::Start(int durationMs)
	{
		ASSERT(durationMs >= 0, std::format("Cannot start timer with a negative duration of {}ms", durationMs).c_str());
		m_StartTime = glfwGetTime();
		m_Duration = durationMs;
		SetState(State::Running);
	}

	void Timer::Restart()
	{
		const float duration = m_Duration;
		Reset();
		Start(duration);
	}

	void Timer::Stop()
	{
		Reset();
	}

	void Timer::Resume()
	{
		if (m_CurrentState == State::Paused)
		{
			m_PausedTime += GetCurrentPauseDuration();
			SetState(State::Running);
		}
	}

	void Timer::Pause()
	{
		if (m_CurrentState == State::Running)
		{
			SetState(State::Paused);
			m_LastPauseTime = glfwGetTime();
		}
	}

	int Timer::GetElapsedTime() const
	{
		const float currentTime = glfwGetTime();
		return ForgeMaths::Max(0, static_cast<int>(m_Duration) - GetRemainingTime());
	}

	int Timer::GetRemainingTime() const
	{
		if (m_CurrentState != State::Stopped)
		{
			const float currentTime = glfwGetTime();
			return ForgeMaths::Max(0, static_cast<int>(m_Duration - (((currentTime - m_StartTime - m_PausedTime - GetCurrentPauseDuration())) * 1000.f)));
		}
		else
		{
			return 0;
		}
	}

	float Timer::GetProgressRatio() const
	{
		return m_Duration == 0 ? 1.f : 1.f - (GetRemainingTime() / static_cast<float>(m_Duration));
	}

	int Timer::GetPauseTime() const
	{
		return static_cast<int>(m_PausedTime * 1000.f + GetCurrentPauseDuration() * 1000.f);
	}

	bool Timer::IsElapsed() const
	{
		return GetRemainingTime() <= 0;
	}

	void Timer::Reset()
	{
		SetState(State::Stopped);
		m_StartTime = 0.f;
		m_PausedTime = 0.f;
		m_LastPauseTime = 0.f;
	}

	void Timer::SetState(State newState)
	{
		m_CurrentState = newState;
	}

	float Timer::GetCurrentPauseDuration() const
	{
		return IsPaused() ? glfwGetTime() - m_LastPauseTime : 0.f;
	}
}