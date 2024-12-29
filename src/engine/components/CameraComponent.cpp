#include "CameraComponent.h"

#include "engine/core/Entity.h"
#include "engine/math/MathUtils.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
    /*static*/ const CameraComponent* CameraComponent::s_ActiveCamera{};

    CameraComponent::CameraComponent(const PerspectiveCamera& cameraData) :
        Mother()
    {
        m_Projection = glm::perspective(glm::radians(cameraData.m_Fov), cameraData.m_AspectRatio, cameraData.m_NearPlane, cameraData.m_FarPlane);
        s_ActiveCamera = this;
    }

    CameraComponent::CameraComponent(const OrthographicCamera& cameraData)
    {
        m_Projection = glm::ortho(0.f, static_cast<float>(cameraData.m_Width), 0.f, static_cast<float>(cameraData.m_Height), cameraData.m_NearPlane, cameraData.m_FarPlane);
        s_ActiveCamera = this;
    }

    void CameraComponent::OnUpdatePreRender(float dT) /*override*/
    {
        Mother::OnUpdatePreRender(dT);
        RefreshView();
    }

    void CameraComponent::OnActivate() /*override*/
    {
        Mother::OnActivate();
        s_ActiveCamera = this;
    }

    void CameraComponent::OnDeactivate() /*override*/
    {
        Mother::OnDeactivate();
        ClearActiveCameraIfNeeded();
    }

    void CameraComponent::OnDestroy() /*override*/
    {
        Mother::OnDestroy();
        ClearActiveCameraIfNeeded();
    }

    void CameraComponent::ClearActiveCameraIfNeeded() /*override*/
    {
        if (s_ActiveCamera == this)
        {
            s_ActiveCamera = nullptr;
        }
    }

    void CameraComponent::RefreshView()
    {
        m_View = Matrix4{ 1.f };
        const Vector3& ownerPosition = GetOwner()->GetPosition();

        ForgeMaths::Translate(m_View, -ownerPosition);

        Vector3 sight{};
        if (m_IsFocusActive && m_FocusedEntity != nullptr)
        {
            sight = m_FocusedEntity->GetTransform().GetPosition() - ownerPosition;
        }
        else
        {
            sight = ForgeMaths::ComputeCameraSight(m_Yaw, m_Pitch);
        }

        m_Sight = ForgeMaths::Normalize(sight);
        m_Right = ForgeMaths::Cross(VECTOR3_UP, m_Sight);
        m_Up = ForgeMaths::Cross(m_Sight, m_Right);

        ForgeMaths::LookAt(m_View, ownerPosition, ownerPosition + m_Sight, VECTOR3_UP);
    }
}