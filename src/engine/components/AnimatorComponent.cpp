#include "AnimatorComponent.h"

#include "engine/anim/Animation.h"
#include "engine/assetloaders/AnimationLoader.h"
#include "engine/core/GameHandler.h"
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

        return true;
    }

#ifdef FORGE_DEBUG_ENABLED
    void AnimatorComponent::OnDrawDebug(float dT) const
    {
        ImGui::Text("Animation: %s", m_Animation.get() != nullptr ? m_Animation.get()->GetDebugName() : "null");
    }
#endif //FORGE_DEBUG_ENABLED
}
