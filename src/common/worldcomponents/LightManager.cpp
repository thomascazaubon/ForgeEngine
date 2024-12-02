#include "LightManager.h"

#include "engine/core/Entity.h"
#include "common/components/LightComponent.h"

#include <algorithm>

namespace ForgeEngine
{
    LightManager::LightManager()
        : Mother()
    {
    }

    void LightManager::RegisterLight(const LightComponent* light)
    {
        if (light != nullptr)
        {
            m_RegisteredLights.push_back(light);
        }
    }

    void LightManager::RemoveLight(const LightComponent* light)
    {
        //TODO: make this fucking easier
        for (auto itr = m_RegisteredLights.begin() ; itr != m_RegisteredLights.end() ; itr++)
        {
            if (*itr == light)
            {
                m_RegisteredLights.erase(itr);
                break;
            }
        }
    }

    std::vector<const LightComponent*> LightManager::GetLightsInRange(const Vector3& position)
    {
        std::vector<const LightComponent*> lights;

        for (const LightComponent* light : m_RegisteredLights)
        {
            if (ForgeMaths::Distance(light->GetOwner()->GetPosition(), position) <= light->GetRange())
            {
                lights.push_back(light);
            }
        }

        return lights;
    }
}
