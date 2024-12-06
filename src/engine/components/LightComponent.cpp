#include "LightComponent.h"

#include "engine/core/GameHandler.h"
#include "engine/worldcomponents/LightManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    LightComponent::LightComponent(float range /*= 1.f*/, float intensity /*= 1.f*/, const Color& color /*= COLOR_WHITE*/)
        : Mother()
        , m_Range(range)
        , m_Intensity(intensity)
        , m_Color(color)
    {
    }

    void LightComponent::OnDestroy()
    {
        GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->RemoveLight(this);
        Mother::OnDestroy();
    }

    bool LightComponent::OnInit() /*override*/
    { 
        Mother::OnInit();

        GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->RegisterLight(this);

        return true; 
    }

#ifdef FORGE_DEBUG_ENABLED
    void LightComponent::OnDrawDebug(float dT) const
    {
        ImGui::Text("Range: %.2f", m_Range);
        ImGui::Text("Intensity: %.2f", m_Intensity);
        ImGui::Text("Color: ");
        ImGui::SameLine();
        ImGui::ColorButton("Color##3c", ImVec4(m_Color.GetR(), m_Color.GetG(), m_Color.GetB(), m_Color.GetA()), 0, ImVec2(50, 15));
    }
#endif //FORGE_DEBUG_ENABLED
}
