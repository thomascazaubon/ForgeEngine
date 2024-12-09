#include "DebugUtils.h"

#include "engine/core/GameHandler.h"
#include "engine/math/Vector3.h"
#include "engine/render/Color.h"
#include "engine/worldcomponents/DebugManager.h"

namespace ForgeEngine
{
    namespace DebugUtils
    {
        void DrawLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration/*= 0.f*/)
        {
            if (DebugManager* debugManager = GameHandler::Get().GetWorld().GetComponentByType<DebugManager>())
            {
                return debugManager->CreateLine(lineStart, lineEnd, color, duration);
            }
        }
    }
}
