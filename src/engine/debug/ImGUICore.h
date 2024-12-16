#pragma once

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#ifdef FORGE_DEBUG_ENABLED
namespace ForgeEngine
{
	class Color;

	namespace ImGUIUtils
	{
		ImVec4 ToImColor(const Color& color);
	}
}
#endif //FORGE_DEBUG_ENABLED