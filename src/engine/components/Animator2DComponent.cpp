#include "Animator2DComponent.h"

#include "engine/anim/Animation2D.h"
#include "engine/anim/Animator2D.h"
#include "engine/assetloaders/Animator2DLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/render/Color.h"
#include "engine/render/Texture.h"
#include "engine/worldcomponents/LightManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    Animator2DComponent::Animator2DComponent(const std::string& animatorPath)
        : Mother()
        , m_AnimatorPath(animatorPath)
        , m_CurrentAnimation("")
    {
    }

    bool Animator2DComponent::OnInit() /*override*/
    {
        Mother::OnInit();

        if (const std::shared_ptr<Animator2D>* animator = GameHandler::Get().GetWorld().GetComponentByType<Animator2DLoader>()->GetOrLoadResource(m_AnimatorPath))
        {
            m_Animator = *animator;
            m_CurrentAnimation = m_Animator.get()->GetDefaultAnimationName();
        }

        return m_Animator.get() != nullptr;
    }

    void Animator2DComponent::OnUpdate(float dT)
    {
        if (m_Timer.IsPaused() || m_Timer.IsElapsed())
        {
            RestartTimer();
        }
    }

    bool Animator2DComponent::SetRunningAnimation(const std::string& name)
    {
        if (m_Animator.get()->HasAnimation(name))
        {
            if (m_CurrentAnimation != name)
            {
                m_CurrentAnimation = name;
                RestartTimer();
            }

            return true;
        }

        return false;
    }

    const Animation2D& Animator2DComponent::GetCurrentAnimation() const
    {
        return *m_Animator.get()->GetAnimation(m_CurrentAnimation);
    }

    const Texture& Animator2DComponent::GetCurrentTexture() const
    {
        return GetCurrentAnimation().GetFrameForProgressRatio(m_Timer.GetProgressRatio());
    }

    void Animator2DComponent::RestartTimer()
    {
        m_Timer.Start(GetCurrentAnimation().GetDuration() * 1000);
    }

#ifdef FORGE_DEBUG_ENABLED
    void Animator2DComponent::OnDrawDebug(float dT) const
    {
        ImGui::Text("Animator: %s", m_Animator.get()->GetDebugName());
        ImGui::Text("States:");
        for (const std::string& state : m_Animator.get()->GetStates())
        {
            const bool isCurrentState = state == m_CurrentAnimation;
            const ImVec4 color = ImGuiUtils::ToImColor(isCurrentState ? COLOR_GREEN : COLOR_WHITE);
            const std::string text = isCurrentState ? std::format("{}[{}]", state.c_str(), GetCurrentAnimation().GetFrameIndexForProgressRatio(m_Timer.GetProgressRatio()))
                : std::format("{}", state.c_str());
            ImGui::TextColored(color, text.c_str());
        }
    }
#endif //FORGE_DEBUG_ENABLED
}
