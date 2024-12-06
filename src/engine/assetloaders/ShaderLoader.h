#pragma once

#include "engine/assetloaders/ResourceLoader.h"

namespace ForgeEngine
{
    class Shader;

	class ShaderLoader : public ResourceLoader<Shader>
	{
		using Mother = ResourceLoader<Shader>;

    public:
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "ShaderLoader"; }
#endif //FORGE_DEBUG_ENABLED

    protected:
        bool AddResource(const std::string& resourcePath) override;

#ifdef FORGE_DEBUG_ENABLED
        void DebugResource(const Shader& resource) const override;
#endif //FORGE_DEBUG_ENABLED
	};
}