#pragma once

#include "engine/core/Object.h"

namespace ForgeEngine
{
    enum class EInputAction
    {
        ToggleWireframe,
        ToggleFreeMouse,
        ToggleImGUI,

        MoveForward,
        MoveBackward,
        MoveRight,
        MoveLeft,
        FlyUp,
        FlyDown,
        DebugFastMove,
        RightClick,
        RightClickOnce,
        LeftClick,
        LeftClickOnce,
        Exit,
        Count
    };

    enum class EInputType
    {
        Hold,
        Press,
        Release,
        Count
    };

    enum class EDeviceTarget
    {
        Keyboard,
        Mouse,
        Gamepad,
        Count
    };

    class Timer;

    //TODO: Make this a loadable resource
    class InputAction : public Object
    {
        using Mother = Object;
        using KeyID = unsigned int;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        private:
            static const constexpr float K_INPUT_THRESHOLD_MS = 0.1f;

            EInputType m_InputType;
            EDeviceTarget m_Target;
            KeyID m_Key;
            bool m_IsActive{ false };
            bool m_NeedsReset{ false };

        /************************************/
        /**************METHODS***************/
        /************************************/

        public:
            InputAction(EInputType type, EDeviceTarget target, KeyID id);

#ifdef FORGE_DEBUG_ENABLED
            //TODO: Fix this
            const char* GetDebugName() const override { return "?"; }
#endif //FORGE_DEBUG_ENABLED

            virtual void Update(float dT);
            bool IsActive() const { return m_IsActive; }

        private:
            bool IsActionPressed() const;

            void ProcessHoldUpdate();
            void ProcessPressUpdate();
            void ProcessReleaseUpdate();
    };
}