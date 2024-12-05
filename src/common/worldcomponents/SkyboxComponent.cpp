#include "SkyboxComponent.h"

#include "engine/core/ForgeEngine.h"
#include "engine/ui/ImGUI.h"
#include "system/math/MathUtils.h"

#include <format>
#include <math.h>

namespace ForgeEngine
{
	SkyboxComponent::SkyboxComponent(float timeScale /*=0.f*/, float startingTimeSeconds /*=NOON_TIME*/)
		: Mother()
		, m_TimeScale(timeScale)
		, m_CurrentSkyColor(COLOR_BLUE)
		, m_CurrentTime(fmodf(startingTimeSeconds, DAY_DURATION_SECONDS))
	{
	}

	void SkyboxComponent::OnUpdate(float dT)
	{
		const float currentTime = m_CurrentTime + dT * m_TimeScale;
		const float excessTime = currentTime - DAY_DURATION_SECONDS;
		m_CurrentTime = fmodf(currentTime, DAY_DURATION_SECONDS) + ForgeMaths::Clamp(excessTime, 0.f, DAY_DURATION_SECONDS);
	}

	float SkyboxComponent::GetAmbientLightIntensity() const
	{
		//TODO: Surely there must be a simpler way to do this shit
		if (m_CurrentTime < DAWN_TIME || m_CurrentTime > DUSK_TIME)
		{
			return 0.f;
		}
		else if (m_CurrentTime >= MAX_LIGHT_TIME_START && m_CurrentTime <= MAX_LIGHT_TIME_END)
		{
			return 1.f;
		}
		else if (m_CurrentTime < MAX_LIGHT_TIME_START)
		{
			return (m_CurrentTime - DAWN_TIME) / (MAX_LIGHT_TIME_START - DAWN_TIME);
		}
		else
		{
			return 1.f - ((m_CurrentTime - MAX_LIGHT_TIME_END) / (DUSK_TIME - MAX_LIGHT_TIME_END));
		}
	}

	bool SkyboxComponent::IsDay() const
	{
		return m_CurrentTime >= DAWN_TIME && m_CurrentTime <= DUSK_TIME;
	}

	Color SkyboxComponent::GetCurrentSkyColor() const
	{
		//TODO: Shitty red shade implementation for dawn and dusk
		return Color(255.f * (1.f - GetAmbientLightIntensity()), COLOR_SKY_BLUE.GetG(), COLOR_SKY_BLUE.GetB()) * GetAmbientLightIntensity();
	}

#ifdef FORGE_DEBUG_ENABLED
	void SkyboxComponent::OnDrawDebug(float dT) const /*override*/
	{
		ImGui::InputFloat("Current time scale", &m_TimeScale, 0.1f, 1.0f, "%.2f");
		ImGui::InputFloat("Current time", &m_CurrentTime, HOUR_DURATION_SECONDS, HOUR_DURATION_SECONDS, "%.0f");
		m_CurrentTime = ForgeMaths::Max(m_CurrentTime, 0.f);
		m_TimeScale = ForgeMaths::Max(m_TimeScale, 0.f);
		const unsigned int timeSeconds = static_cast<unsigned int>(m_CurrentTime);
		const unsigned int hours = static_cast<unsigned int>(timeSeconds / HOUR_DURATION_SECONDS);
		const unsigned int minutes = static_cast<unsigned int>((timeSeconds - (hours * 3600)) / 60.f);
		const unsigned int seconds = (timeSeconds - (hours * 3600)) % 60;
		ImGui::Text(std::format("Current time: {:02}:{:02}:{:02}", hours, minutes, seconds).c_str());
		ImGui::Text("Current ambient light intensity: %.2f", GetAmbientLightIntensity());
	}
#endif //FORGE_DEBUG_ENABLED
}