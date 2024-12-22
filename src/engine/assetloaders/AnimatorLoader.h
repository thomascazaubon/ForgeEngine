#pragma once

#include "engine/anim/Animator.h"
#include "engine/assetloaders/AssetLoader.h"

namespace ForgeEngine
{
    class Animation;

    class AnimatorLoader : public AssetLoader<Animator>
    {
        using Mother = AssetLoader<Animator>;

    public:
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "AnimatorLoader"; }
#endif //FORGE_DEBUG_ENABLED
    };
}
