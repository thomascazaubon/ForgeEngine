#pragma once

#include "engine/input/InputAction.h"
#include "engine/math/Vector2.h"

namespace ForgeEngine
{
    enum class EInputAction;

    namespace InputHelper
    {
        bool IsInputActive(EInputAction type);
        Vector2 GetMouseVelocity();
        Vector2 GetMousePosition();
    }
}