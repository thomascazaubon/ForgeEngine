#pragma once

#include "engine/assetloaders/AssetLoader.h"

namespace ForgeEngine
{
    class Material;

    class MaterialLoader : public AssetLoader<Material>
    {
        using Mother = AssetLoader<Material>;

        public:
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "MaterialLoader"; }
#endif //FORGE_DEBUG_ENABLED

        protected:
            bool AddResource(const std::string& resourcePath) override;

#ifdef FORGE_DEBUG_ENABLED
            void DebugResource(const Material& resource) const override;
#endif //FORGE_DEBUG_ENABLED
    };
}
