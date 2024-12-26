#pragma once

#include "engine/anim/Animation2D.h"
#include "engine/assetloaders/AssetLoader.h"

namespace ForgeEngine
{
    class Animation2D;

    class Animation2DLoader : public AssetLoader<Animation2D>
    {
        using Mother = AssetLoader<Animation2D>;

    public:
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "Animation2DLoader"; }
#endif //FORGE_DEBUG_ENABLED
    };
}
