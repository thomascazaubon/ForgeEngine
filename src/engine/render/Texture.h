#pragma once

#include "engine/assetloaders/LoadableAsset.h"
#include "engine/render/OpenGL.h"

#include <string>

namespace ForgeEngine
{
    class Texture : public LoadableAsset
    {
        using Mother = LoadableAsset;

        public:
            Texture(const std::string& texturePath, unsigned int rgbaMode = GL_RGBA, bool flip = true);
            Texture(void* data, unsigned int width, unsigned int height);
            ~Texture();

            //TODO: fix this
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return m_Name.c_str(); }
            void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED

            bool IsValid() const override { return m_GLTexture; }

            int GetWidth() const { return m_Width; }
            int GetHeight() const { return m_Height; }

            unsigned int GetGLTexture() const { return m_GLTexture; }
            void Use();

        private:
            unsigned int m_GLTexture{};

            int m_Width{};
            int m_Height{};
            int m_Channels{};

            const std::string m_Name;
    };
}
