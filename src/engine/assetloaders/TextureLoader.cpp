#include "TextureLoader.h"

#include "engine/render/Texture.h"

namespace ForgeEngine
{
    bool TextureLoader::AddResource(const std::string& resourcePath)
    {
        Texture* texture = new Texture(resourcePath.c_str());

        if (texture->IsValid())
        {
            m_LoadedResources[resourcePath] = std::shared_ptr<Texture>(texture);
        }
        else
        {
            delete(texture);
            texture = nullptr;
        }

        return texture;
    }

#ifdef FORGE_DEBUG_ENABLED
    void TextureLoader::DebugResource(const Texture& resource) const
    {
        resource.OnDrawDebug();
    }
#endif //FORGE_DEBUG_ENABLED
}