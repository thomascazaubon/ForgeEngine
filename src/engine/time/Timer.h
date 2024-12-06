#pragma once

namespace ForgeEngine
{
	class Timer
	{
		enum class State
		{
			Stopped,
			Running,
			Paused
		};

		public:
			void Start(int durationMs);
			void Restart();
			void Pause();
			void Resume();
			void Stop();

			bool IsStarted() const { return m_CurrentState == State::Running; }
			bool IsPaused() const { return m_CurrentState == State::Paused; }
			bool IsElapsed() const;
			int GetElapsedTime() const;
			int GetRemainingTime() const;
			float GetProgressRatio() const;
			int GetDuration() const { return m_Duration; }
			int GetPauseTime() const;

		private:
			void Reset();
			void SetState(State newState);
			float GetCurrentPauseDuration() const;

			unsigned int m_Duration{ 0 };
			float m_StartTime{ 0.f };
			float m_LastPauseTime{ 0.f };
			float m_PausedTime{ 0.f};
			State m_CurrentState{ State::Stopped };
	};
}