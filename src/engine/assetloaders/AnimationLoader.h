#pragma once

#include "engine/anim/Animation.h"
#include "engine/assetloaders/AssetLoader.h"

namespace ForgeEngine
{
    class Animation;

    class AnimationLoader : public AssetLoader<Animation>
    {
        using Mother = AssetLoader<Animation>;

    public:
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "AnimationLoader"; }
#endif //FORGE_DEBUG_ENABLED
    };
}
