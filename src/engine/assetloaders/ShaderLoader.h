#pragma once

#include "engine/assetloaders/AssetLoader.h"
#include "engine/render/Shader.h"

#define DEFAULT_SHADER_PATH                     "assets\\shaders\\default"
#define TEXTURED_SHADER_PATH                    "assets\\shaders\\textured"
#define LIT_SHADER_PATH                         "assets\\shaders\\lit"
#define DEBUG_SHADER_PATH                       "assets\\shaders\\debug"

namespace ForgeEngine
{
    class Shader;

    class ShaderLoader : public AssetLoader<Shader>
    {
        using Mother = AssetLoader<Shader>;

        public:
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "ShaderLoader"; }
#endif //FORGE_DEBUG_ENABLED
    };
}