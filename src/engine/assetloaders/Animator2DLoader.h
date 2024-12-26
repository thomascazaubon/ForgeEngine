#pragma once

#include "engine/anim/Animator2D.h"
#include "engine/assetloaders/AssetLoader.h"

namespace ForgeEngine
{
    class Animation2D;

    class Animator2DLoader : public AssetLoader<Animator2D>
    {
        using Mother = AssetLoader<Animator2D>;

    public:
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "AnimatorLoader"; }
#endif //FORGE_DEBUG_ENABLED
    };
}
