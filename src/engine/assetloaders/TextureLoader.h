#pragma once

#include "engine/assetloaders/AssetLoader.h"

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

        protected:
            bool AddResource(const std::string& resourcePath) override;

#ifdef FORGE_DEBUG_ENABLED
            void DebugResource(const Texture& resource) const override;
#endif //FORGE_DEBUG_ENABLED
    };
}
