#pragma once

#ifdef FORGE_DEBUG_ENABLED
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <string>

namespace ForgeEngine
{
	class Color;

	namespace ImGUIUtils
	{
		ImVec4 ToImColor(const Color& color);
		ImVec4 GetShaderVariableTypeColor(const std::string& type);
	}
}
#endif //FORGE_DEBUG_ENABLED