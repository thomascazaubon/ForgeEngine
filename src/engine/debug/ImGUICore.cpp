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
	}
}
#endif //FORGE_DEBUG_ENABLED