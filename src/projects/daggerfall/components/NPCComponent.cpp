#include "NPCComponent.h"

#include "engine/components/Animator2DComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/core/Entity.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    bool NPCComponent::OnInit()
    {
        bool initSuccess = Mother::OnInit();
        m_AnimatorComponent = GetOwner()->GetComponentByType<Animator2DComponent>();
        return initSuccess && m_AnimatorComponent != nullptr;
    }

    void NPCComponent::OnUpdate(float dT)
    {
        const CameraComponent* playerCamera = CameraComponent::GetActiveCamera();
        const Vector3& playerPosition = playerCamera != nullptr ? playerCamera->GetOwner()->GetPosition() : VECTOR3_NULL;
        const Vector3& ownerPosition = GetOwner()->GetPosition();

        const Vector3& playerPositionFlat = Vector3(playerPosition.x, ownerPosition.y, playerPosition.z);
        const Vector3 toPlayer = playerPositionFlat - ownerPosition;
        if (m_AnimatorComponent)
        {
            if (glm::length(toPlayer) > 3.f)
            {
                GetOwner()->GetTransform().Translate(ForgeMaths::Normalize(toPlayer) * 5.f * dT);
                m_AnimatorComponent->SetRunningAnimation("walk");
            }
            else
            {
                m_AnimatorComponent->SetRunningAnimation("idle");
            }
        }
    }
}
