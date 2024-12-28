#pragma once

#include "engine/assetloaders/LoadableAsset.h"
#include "engine/render/Color.h"

#include <string>

namespace ForgeEngine
{
    class Texture;

    class Material : public LoadableAsset
    {
        using Mother = LoadableAsset;

        template<typename T>
        friend class AssetLoader;

        public:
            bool IsValid() const override { return true; }
            int GetShininess() const { return m_Shininess; }
            float GetSpecular() const { return m_Specular; }
            float GetDiffuse() const { return m_Diffuse; }
            float GetTextureHeight() const { return m_TextureHeight; }
            const Color& GetColor() const { return m_Color; }
            const Texture* GetTexture() const { return m_Texture.get(); }

        private:
            Material(const std::string& path);
            bool ResolveAttribute(const std::string& name, const std::string& value);

            void SetColor(Color color) { m_Color = color; }

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED

            int m_Shininess{ 2 };
            float m_Diffuse{ 1.f };
            float m_Specular{ 0.f };
            float m_TextureHeight{ 0.f };
            Color m_Color{ COLOR_MAGENTA };
            std::shared_ptr<Texture> m_Texture{ nullptr };
    };
}