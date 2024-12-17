#include "ImGUICore.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/render/Color.h"

namespace ForgeEngine
{
    namespace ImGUIUtils
    {
        ImVec4 ToImColor(const Color& color)
        {
            return ImVec4(color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA());
        }

        ImVec4 GetShaderVariableTypeColor(const std::string& type)
        {
            if (type == "bool")
            {
                return ImGUIUtils::ToImColor(COLOR_RED);
            }
            if (type == "float")
            {
                return ImGUIUtils::ToImColor(COLOR_GREEN);
            }
            if (type == "int")
            {
                return ImGUIUtils::ToImColor(COLOR_BLUE);
            }
            if (type == "vec3")
            {
                return ImGUIUtils::ToImColor(COLOR_PURPLE);
            }
            if (type == "vec4")
            {
                return ImGUIUtils::ToImColor(COLOR_PURPLE);
            }
            if (type == "mat3")
            {
                return ImGUIUtils::ToImColor(COLOR_YELLOW);
            }
            if (type == "mat4")
            {
                return ImGUIUtils::ToImColor(COLOR_YELLOW);
            }
            if (type == "sampler2D")
            {
                return ImGUIUtils::ToImColor(COLOR_CYAN);
            }

            return ImGUIUtils::ToImColor(COLOR_ORANGE);
        }
    }
}
#endif //FORGE_DEBUG_ENABLED