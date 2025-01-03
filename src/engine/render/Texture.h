#pragma once

#include "engine/assetloaders/LoadableAsset.h"
#include "engine/render/OpenGL.h"

#include <string>

namespace ForgeEngine
{
    class Texture : public LoadableAsset
    {
        using Mother = LoadableAsset;

        template<typename T>
        friend class AssetLoader;

        public:
            ~Texture();

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED

            bool IsValid() const override { return m_GLTexture; }

            int GetWidth() const { return m_Width; }
            int GetHeight() const { return m_Height; }

            unsigned int GetGLTexture() const { return m_GLTexture; }
            void Use();

        private:
            Texture(const std::string& texturePath);

            unsigned int m_GLTexture{};

            int m_Width{};
            int m_Height{};
            int m_Channels{};
    };
}
