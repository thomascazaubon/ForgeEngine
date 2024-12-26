#include "FirstPersonControllerComponent.h"

#include "engine/components/CameraComponent.h"
#include "engine/core/Entity.h"
#include "engine/core/GameHandler.h"
#include "engine/input/InputHelper.h"
#include "engine/math/MathUtils.h"
#include "engine/math/Vector2.h"
#include "engine/math/Vector3.h"
#include "engine/render/OpenGL.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#include "engine/worldcomponents/DebugManager.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    FirstPersonControllerComponent::FirstPersonControllerComponent(float moveSpeed /*= 10.f*/, float rotationSpeed /*= 10.f*/) 
        : Component()
        , m_MoveSpeed(moveSpeed)
        , m_RotationSpeed(rotationSpeed)
    {
    }

    bool FirstPersonControllerComponent::OnInit() /*override*/
    {
        bool success = Mother::OnInit();

        m_CameraComponent = GetOwner()->GetComponentByType<CameraComponent>();
        glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        return success
            && m_CameraComponent != nullptr;
    }

    void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);

        Vector3 translation = VECTOR3_NULL;
        Vector2 mouseVelocity = InputHelper::GetMouseVelocity();
        float yaw = m_CameraComponent->GetYaw() - (mouseVelocity.x * m_RotationSpeed * dT);
        float pitch = ForgeMaths::Clamp(m_CameraComponent->GetPitch() + (mouseVelocity.y * m_RotationSpeed * dT), -89.f, 89.f);

        Vector3 cameraSightFlattened = ForgeMaths::FlattenAndNormalize(m_CameraComponent->GetSight());

        if (InputHelper::IsInputActive(EInputAction::MoveForward))
        {
            translation += cameraSightFlattened;
        }
        if (InputHelper::IsInputActive(EInputAction::MoveBackward))
        {
            translation -= cameraSightFlattened;
        }
        if (InputHelper::IsInputActive(EInputAction::MoveLeft))
        {
            translation += m_CameraComponent->GetRight();
        }
        if (InputHelper::IsInputActive(EInputAction::MoveRight))
        {
            translation -= m_CameraComponent->GetRight();
        }

        if (InputHelper::IsInputActive(EInputAction::FlyUp))
        {
            translation += VECTOR3_UP;
        }
        if (InputHelper::IsInputActive(EInputAction::FlyDown))
        {
            translation -= VECTOR3_UP;
        }

        bool areControlsEnabled = true;
#ifdef FORGE_DEBUG_ENABLED
        const DebugManager* debugManager = GameHandler::Get().GetWorld().GetComponentByType<const DebugManager>();
        areControlsEnabled = debugManager == nullptr || !debugManager->IsFreeMouseEnabled();
#endif //FORGE_DEBUG_ENABLED

        if (areControlsEnabled)
        {
            m_CameraComponent->SetYaw(yaw);
            m_CameraComponent->SetPitch(pitch);
            Vector3 finalTranslation = translation != VECTOR3_NULL ? glm::normalize(translation) * m_MoveSpeed * dT : VECTOR3_NULL;
            GetOwner()->GetTransform().Translate(finalTranslation);
        }
    }
#ifdef FORGE_DEBUG_ENABLED
    void FirstPersonControllerComponent::OnDrawDebug(float dT) const  /*override*/
    {
        const Vector3& playerPosition = GetOwner()->GetPosition();
        ImGui::Text("Player Position: (%.2f, %.2f, %.2f)", playerPosition.x, playerPosition.y, playerPosition.z);
    }
#endif //FORGE_DEBUG_ENABLED

    void FirstPersonControllerComponent::OnDestroy() /*override*/
    {
        glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Mother::OnDestroy();
    }
}
