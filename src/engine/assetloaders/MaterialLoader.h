#pragma once

#include "engine/assetloaders/AssetLoader.h"
#include "engine/render/Material.h"

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
    };
}
