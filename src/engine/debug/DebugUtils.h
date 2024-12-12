#pragma once

#include "engine/math/Vector3.h"

#include <string>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    class Color;

    namespace DebugUtils
    {
        void DrawLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration = 0.f);

        void Log(const std::string& log);
        void LogWarning(const std::string& warning);
        void LogError(const std::string& error);
    }
#endif //FORGE_DEBUG_ENABLED
}
