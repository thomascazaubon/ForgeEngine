#include "InputManager.h"

#include "engine/core/ForgeEngine.h"

namespace ForgeEngine
{
    InputManager::InputManager() :
        Mother()
    {
        m_InputActionMappings[EInputAction::ToggleWireframe]    = std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_F1 });
        m_InputActionMappings[EInputAction::ToggleImGUI]        = std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_F2 });
        m_InputActionMappings[EInputAction::ToggleFreeMouse]    = std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_TAB });
        m_InputActionMappings[EInputAction::RightClickOnce]        = std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_RIGHT });
        m_InputActionMappings[EInputAction::LeftClickOnce]        = std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_LEFT });

        m_InputActionMappings[EInputAction::MoveForward]        = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_W });
        m_InputActionMappings[EInputAction::MoveBackward]        = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_S });
        m_InputActionMappings[EInputAction::MoveRight]            = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_D });
        m_InputActionMappings[EInputAction::MoveLeft]            = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_A });
        m_InputActionMappings[EInputAction::RightClick]            = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_RIGHT });
        m_InputActionMappings[EInputAction::LeftClick]            = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_LEFT });
        m_InputActionMappings[EInputAction::FlyUp]                = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_SPACE });
        m_InputActionMappings[EInputAction::FlyDown]            = std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_C });

        m_InputActionMappings[EInputAction::Exit]                = std::unique_ptr<InputAction>(new InputAction{ EInputType::Release, EDeviceTarget::Keyboard, GLFW_KEY_ENTER });
    }

    void InputManager::OnUpdatePreRender(float dT) /*override*/
    {
        Mother::OnUpdatePreRender(dT);
        for (auto& inputAction : m_InputActionMappings)
        {
            inputAction.second.get()->Update(dT);
        }
        UpdateMousePosition();
    }

    bool InputManager::IsInputActive(EInputAction actionType) const
    {
        auto it = m_InputActionMappings.find(actionType);
        return it != m_InputActionMappings.end()
            && ((*it).second).get()->IsActive();
    }

    void InputManager::UpdateMousePosition()
    {
        double x, y;
        glfwGetCursorPos(GameHandler::Get().GetWindow(), &x, &y);
        m_PreviousMousePosition = m_MousePosition;
        m_MousePosition = Vector2{ x, y };
    }
}