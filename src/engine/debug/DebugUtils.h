#pragma once

#include "engine/math/Vector3.h"

#include <format>
#include <string>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    class Color;

    namespace DebugUtils
    {
        void DrawLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration = 0.f);

        void Log(const std::string& log);
        template<typename... Args>
        void Log(const char* format, Args&&... args)
        {
            Log(std::vformat(format, std::make_format_args(args...)));
        }

        void LogWarning(const std::string& warning);
        template<typename... Args>
        void LogWarning(const char* format, Args&&... args)
        {
            LogWarning(std::vformat(format, std::make_format_args(args...)));
        }

        void LogError(const std::string& error);
        template<typename... Args>
        void LogError(const char* format, Args&&... args)
        {
            LogError(std::vformat(format, std::make_format_args(args...)));
        }
    }
#endif //FORGE_DEBUG_ENABLED
}
