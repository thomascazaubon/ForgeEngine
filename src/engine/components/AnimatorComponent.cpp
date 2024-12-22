#include "AnimatorComponent.h"

#include "engine/anim/Animation.h"
#include "engine/assetloaders/AnimationLoader.h"
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
    {
    }

    bool AnimatorComponent::OnInit() /*override*/
    {
        Mother::OnInit();

        if (const std::shared_ptr<Animation>* animation = GameHandler::Get().GetWorld().GetComponentByType<AnimationLoader>()->GetOrLoadResource(m_AnimatorPath))
        {
            m_Animation = *animation;
        }

        return m_Animation.get() != nullptr;
    }

    void AnimatorComponent::OnPreUpdate(float dT)
    {
        if (m_Timer.IsPaused() || m_Timer.IsElapsed())
        {
            m_Timer.Start(m_Animation.get()->GetDuration() * 1000);
        }
    }

    const Texture& AnimatorComponent::GetTexture() const 
    { 
        return m_Animation.get()->GetFrameForProgressRatio(m_Timer.GetProgressRatio()); 
    }

#ifdef FORGE_DEBUG_ENABLED
    void AnimatorComponent::OnDrawDebug(float dT) const
    {
        ImGui::Text("Animation: %s", m_Animation.get()->GetDebugName());
        ImGui::Text("Current frame: %s", GetTexture().GetDebugName());
    }
#endif //FORGE_DEBUG_ENABLED
}
