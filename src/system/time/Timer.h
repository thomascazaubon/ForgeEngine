#pragma once

#include "engine/core/Object.h"

namespace ForgeEngine
{
	//Time expressed in seconds
	class Timer : public Object
	{
		using Mother = Object;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_Duration{ 0.f };
			float m_ElapsedTime{ 0.f };
			bool m_IsStarted{ false };
			bool m_IsPaused{ false };
			bool m_IsElapsed{ false };
			bool m_IsInitialized{ false };

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			void Start(float duration);
			void Pause() { m_IsStarted = false; }
			void Resume();
			void Stop();

			void Update(float dT);

			bool IsStarted() const { return m_IsStarted; }
			bool IsElapsed() const { return m_IsElapsed && m_IsStarted; }
	};
}