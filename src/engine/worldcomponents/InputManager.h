#pragma once

#include "engine/input/InputAction.h"
#include "engine/math/Vector2.h"
#include "engine/worldcomponents/WorldComponent.h"

#include <memory>
#include <unordered_map>

namespace ForgeEngine
{
    class InputManager : public WorldComponent
    {
        using Mother = WorldComponent;

        public:
            InputManager();

            virtual void OnPreUpdate(float dT) override;

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "InputManager"; }
#endif //FORGE_DEBUG_ENABLED

            bool IsInputActive(EInputAction actionType) const;
            Vector2 GetMousePosition() const { return m_MousePosition; };
            Vector2 GetMouseVelocity() const { return (m_PreviousMousePosition - m_MousePosition); };

        private:
            void UpdateMousePosition();

            std::unordered_map<EInputAction, std::unique_ptr<InputAction>> m_InputActionMappings{};
            Vector2 m_MousePosition{};
            Vector2 m_PreviousMousePosition{};
    };
}