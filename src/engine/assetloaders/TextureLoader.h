#pragma once

#include "engine/assetloaders/ResourceLoader.h"

namespace ForgeEngine
{
    class Texture;

    class TextureLoader : public ResourceLoader<Texture>
    {
        using Mother = ResourceLoader<Texture>;

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
