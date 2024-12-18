#include "ImGUICore.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/render/Color.h"

namespace ForgeEngine
{
    namespace ImGuiUtils
    {
        void PushId(int seed)
        {
            srand(seed);
            ImGui::PushID(seed + rand());
        }

        ImVec4 ToImColor(const Color& color)
        {
            return ImVec4(color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA());
        }

        ImVec4 GetShaderVariableTypeColor(const std::string& type)
        {
            if (type == "bool")
            {
                return ImGuiUtils::ToImColor(COLOR_RED);
            }
            if (type == "float")
            {
                return ImGuiUtils::ToImColor(COLOR_GREEN);
            }
            if (type == "int")
            {
                return ImGuiUtils::ToImColor(COLOR_BLUE);
            }
            if (type == "vec3")
            {
                return ImGuiUtils::ToImColor(COLOR_PURPLE);
            }
            if (type == "vec4")
            {
                return ImGuiUtils::ToImColor(COLOR_PURPLE);
            }
            if (type == "mat3")
            {
                return ImGuiUtils::ToImColor(COLOR_YELLOW);
            }
            if (type == "mat4")
            {
                return ImGuiUtils::ToImColor(COLOR_YELLOW);
            }
            if (type == "sampler2D")
            {
                return ImGuiUtils::ToImColor(COLOR_CYAN);
            }

            return ImGuiUtils::ToImColor(COLOR_ORANGE);
        }
    }
}
#endif //FORGE_DEBUG_ENABLED