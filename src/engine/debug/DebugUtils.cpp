#include "DebugUtils.h"

#include "engine/core/GameHandler.h"
#include "engine/render/Color.h"
#include "engine/worldcomponents/DebugManager.h"

#include <windows.h>

#ifdef FORGE_DEBUG_ENABLED
namespace ForgeEngine
{
    namespace DebugUtils
    {
        namespace Private
        {
            #define LOG_COLOR_RED 12
            #define LOG_COLOR_YELLOW 6
            #define LOG_COLOR_WHITE 7

            /*
            1: blue
            2: green
            3: cyan
            4: red
            5: purple
            6: yellow (dark)
            7: default white
            8: gray/grey
            9: bright blue
            10: bright green
            11: bright cyan
            12: bright red
            13: pink/magenta
            14: yellow
            15: bright white
            */
            void WriteToConsole(const char* text, unsigned int color)
            {
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, color);
                std::cout << text << std::endl;
                SetConsoleTextAttribute(h, LOG_COLOR_WHITE);
            }
        }

        void DrawLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration/*= 0.f*/)
        {
            if (DebugManager* debugManager = GameHandler::Get().GetWorld().GetComponentByType<DebugManager>())
            {
                return debugManager->CreateLine(lineStart, lineEnd, color, duration);
            }
        }

        void Log(const std::string& log)
        {
            Private::WriteToConsole(log.c_str(), LOG_COLOR_WHITE);
        }

        void LogWarning(const std::string& warning)
        {
            Private::WriteToConsole(std::string("Warning: " + warning).c_str(), LOG_COLOR_YELLOW);
        }

        void LogError(const std::string& error)
        {
            Private::WriteToConsole(std::string("ERROR: " + error).c_str(), LOG_COLOR_RED);
        }

        std::string ToString(const Vector3& vector)
        {
            return std::format("[{:.2f};{:.2f};{:.2f}]", vector.x, vector.y, vector.z);
        }

        std::string ToString(const Vector4& vector)
        {
            return std::format("[{:.2f};{:.2f};{:.2f};{:.2f}]", vector.x, vector.y, vector.z, vector.w);
        }

        std::string ToString(const Matrix4& matrix)
        {
            return std::format("{:.2f};{:.2f};{:.2f};{:.2f}\n{:.2f};{:.2f};{:.2f};{:.2f}\n{:.2f};{:.2f};{:.2f};{:.2f}\n{:.2f};{:.2f};{:.2f};{:.2f}", 
                matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
                matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
                matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
                matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
        }
    }
}
#endif //FORGE_DEBUG_ENABLED
