#include "InputAction.h"

#include "engine/core/GameHandler.h"
#include "engine/render/OpenGL.h"

namespace ForgeEngine
{
    InputAction::InputAction(EInputType type, EDeviceTarget target, KeyID id) :
        Mother(),
        m_InputType(type),
        m_Target(target),
        m_Key(id)
    {
    }

    bool InputAction::IsActionPressed() const
    {
        bool isActionPressed{ false };
        switch (m_Target)
        {
            case(EDeviceTarget::Keyboard):
                isActionPressed = (glfwGetKey(GameHandler::Get().GetWindow(), m_Key) == GLFW_PRESS);
                break;
            case(EDeviceTarget::Mouse):
                isActionPressed = (glfwGetMouseButton(GameHandler::Get().GetWindow(), m_Key) == GLFW_PRESS);
                break;
        }
        return isActionPressed;
    }

    void InputAction::Update(float dT)
    {
        switch (m_InputType)
        {
            case (EInputType::Hold):
                ProcessHoldUpdate();
                break;
            case (EInputType::Press):
                ProcessPressUpdate();
                break;
            case (EInputType::Release):
                ProcessReleaseUpdate();
                break;
        }
    }

    void InputAction::ProcessHoldUpdate()
    {
        m_IsActive = IsActionPressed();
    }

    void InputAction::ProcessPressUpdate()
    {
        if (IsActionPressed() && !m_NeedsReset)
        {
            m_NeedsReset = true;
            m_IsActive = true;
        }
        else if (m_NeedsReset)
        {
            m_IsActive = false;
            m_NeedsReset = IsActionPressed();
        }
    }

    void InputAction::ProcessReleaseUpdate()
    {
        if (IsActionPressed() && !m_NeedsReset)
        {
            m_NeedsReset = true;
        }
        else if (m_NeedsReset)
        {
            if (!IsActionPressed())
            {
                m_NeedsReset = false;
                m_IsActive = true;
            }
        }
        else
        {
            m_IsActive = false;
        }
    }
}