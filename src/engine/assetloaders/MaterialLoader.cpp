#include "MaterialLoader.h"

#include "engine/io/FileUtils.h"
#include "engine/render/Material.h"

namespace ForgeEngine
{
    bool MaterialLoader::AddResource(const std::string& resourcePath)
    {
        std::string resourceContent;
        bool success = resourcePath == DEFAULT_RESOURCE_NAME || FileUtils::TryLoadFileContent(resourcePath, resourceContent);

        if (success)
        {
            m_LoadedResources[resourcePath] = std::shared_ptr<Material>(new Material(resourceContent
#ifdef FORGE_DEBUG_ENABLED
                , resourcePath.c_str()
#endif //FORGE_DEBUG_ENABLED            
            ));
        }

        return success;
    }

#ifdef FORGE_DEBUG_ENABLED
    void MaterialLoader::DebugResource(const Material& resource) const
    {
        resource.OnDrawDebug();
    }
#endif //FORGE_DEBUG_ENABLED
}