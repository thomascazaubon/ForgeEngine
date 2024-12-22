#include "AnimatorComponent.h"

#include "engine/anim/Animation.h"
#include "engine/assetloaders/AnimatorLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/render/Texture.h"
#include "engine/worldcomponents/LightManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    AnimatorComponent::AnimatorComponent(const std::string& animatorPath)
        : Mother()
        , m_AnimatorPath(animatorPath)
        , m_CurrentAnimation("")
    {
    }

    bool AnimatorComponent::OnInit() /*override*/
    {
        Mother::OnInit();

        if (const std::shared_ptr<Animator>* animator = GameHandler::Get().GetWorld().GetComponentByType<AnimatorLoader>()->GetOrLoadResource(m_AnimatorPath))
        {
            m_Animator = *animator;
            m_CurrentAnimation = m_Animator.get()->GetDefaultAnimationName();
        }

        return m_Animator.get() != nullptr;
    }

    void AnimatorComponent::OnPreUpdate(float dT)
    {
        if (m_Timer.IsPaused() || m_Timer.IsElapsed())
        {
            RestartTimer();
        }
    }

    bool AnimatorComponent::SetRunningAnimation(const std::string& name)
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

    const Animation& AnimatorComponent::GetCurrentAnimation() const
    {
        return *m_Animator.get()->GetAnimation(m_CurrentAnimation);
    }

    const Texture& AnimatorComponent::GetCurrentTexture() const
    {
        return GetCurrentAnimation().GetFrameForProgressRatio(m_Timer.GetProgressRatio());
    }

    void AnimatorComponent::RestartTimer()
    {
        m_Timer.Start(GetCurrentAnimation().GetDuration() * 1000);
    }

#ifdef FORGE_DEBUG_ENABLED
    void AnimatorComponent::OnDrawDebug(float dT) const
    {
        ImGui::Text("Animator: %s", m_Animator.get()->GetDebugName());
        ImGui::Text("Now playing: %s[%d]", m_CurrentAnimation.c_str(), GetCurrentAnimation().GetFrameIndexForProgressRatio(m_Timer.GetProgressRatio()));
    }
#endif //FORGE_DEBUG_ENABLED
}
