#pragma once

#include "system/math/Vector3.h"

namespace ForgeEngine
{
    class Color;

    namespace DebugUtils
    {
        void DrawLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color);
    }
}
