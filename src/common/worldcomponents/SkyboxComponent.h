#pragma once

#include "engine/core/WorldComponent.h"
#include "system/misc/Color.h"

namespace ForgeEngine
{
    #define MAX_LIGHT_TIME_START 36000.f //11h
    #define MAX_LIGHT_TIME_END 64800.f //18h
    #define DAWN_TIME 21600.f //6h
    #define NOON_TIME 43200.f //12h
    #define DUSK_TIME 75600.f //21h
    #define MIDNIGHT_TIME 0.f //0h
    #define DAY_DURATION_SECONDS 86400.f
    #define HOUR_DURATION_SECONDS 3600.f

    class SkyboxComponent : public WorldComponent
    {
        using Mother = WorldComponent;

    public:
        SkyboxComponent(float timeScale = 0.f, float startingTimeSeconds = NOON_TIME);

        void OnUpdate(float dT) override;

        bool IsDay() const;
        bool IsNight() const { return !IsDay(); }
        float GetAmbientLightIntensity() const;
        Color GetCurrentSkyColor() const;

#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "SkyBoxComponent"; }

        void OnDrawDebug(float dT) const override;
#endif //FORGE_DEBUG_ENABLED

    private:
        mutable float m_CurrentTime{ 0.f };
        mutable float m_TimeScale{ 1.f };
        Color m_CurrentSkyColor;
    };
}