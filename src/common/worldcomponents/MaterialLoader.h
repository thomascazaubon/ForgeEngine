#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Material;

    class MaterialLoader : public ResourceLoader<Material>
    {
        using Mother = ResourceLoader<Material>;

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
