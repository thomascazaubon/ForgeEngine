#pragma once

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUI.h"

namespace ForgeEngine
{
	class Color;

	namespace ImGUIUtils
	{
		ImVec4 ToImColor(const Color& color);
	}
}
#endif //FORGE_DEBUG_ENABLED
