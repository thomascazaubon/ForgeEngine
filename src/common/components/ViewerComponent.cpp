#include "ViewerComponent.h"

#include "engine/core/ForgeEngine.h"
#include "engine/math/Vector3.h"

namespace ForgeEngine
{
    ViewerComponent::ViewerComponent(float translationSpeed, float rotationSpeed, float scaleSpeed) :
        Mother(),
        m_TranslationSpeed(translationSpeed),
        m_RotationSpeed(rotationSpeed),
        m_ScaleSpeed(scaleSpeed)
    {
    }

    void ViewerComponent::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);

        Vector3 eulerRotation{};
        Vector3 translation{};
        Vector3 scale{ 1.f };

        //Translation
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            translation.y += m_TranslationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            translation.y -= m_TranslationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            translation.x -= m_TranslationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            translation.x += m_TranslationSpeed;
        }

        //Rotation
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            eulerRotation.y += m_RotationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            eulerRotation.y -= m_RotationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        {
            eulerRotation.x -= m_RotationSpeed;
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            eulerRotation.x += m_RotationSpeed;
        }

        //Scale
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        {
            scale *= (1.f / m_ScaleSpeed);
        }
        if (glfwGetKey(GameHandler::Get().GetWindow(), GLFW_KEY_KP_ADD) == GLFW_PRESS)
        {
            scale *= m_ScaleSpeed;
        }

        m_Owner->GetTransform().Rotate(eulerRotation * dT);
        m_Owner->GetTransform().Translate(translation * dT);
        m_Owner->GetTransform().Scale(scale);
    }
}