#include "ShaderLoader.h"

#include "engine/io/FileUtils.h"
#include "engine/render/Shader.h"

#ifdef FORGE_DEBUG_ENABLED
//#include <memory>
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    bool ShaderLoader::AddResource(const std::string& resourcePath)
    {
        Shader* shader = new Shader(resourcePath);

        if (shader->IsValid())
        {
            m_LoadedResources[resourcePath] = std::shared_ptr<Shader>(shader);
        }
        else
        {
            delete(shader);
            shader = nullptr;
        }

        return shader;
    }

#ifdef FORGE_DEBUG_ENABLED
    void ShaderLoader::DebugResource(const Shader& resource) const
    {
        resource.OnDrawDebug();
    }

    void ShaderLoader::OnPreUpdate(float dT)
    {
        for (const auto& shader : m_LoadedResources)
        {
            shader.second.get()->ClearRecordedData();
        }
    }
#endif //FORGE_DEBUG_ENABLED
}