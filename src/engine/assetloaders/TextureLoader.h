#pragma once

#include "engine/assetloaders/AssetLoader.h"
#include "engine/render/Texture.h"

namespace ForgeEngine
{
    class Texture;

    class TextureLoader : public AssetLoader<Texture>
    {
        using Mother = AssetLoader<Texture>;

        public:
    #ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "TextureLoader"; }
    #endif //FORGE_DEBUG_ENABLED
    };
}
