#include "ShaderLoader.h"

#include "engine/shader/Shader.h"
#include "system/io/FileUtils.h"

namespace ForgeEngine
{
    bool ShaderLoader::AddResource(const std::string& resourcePath)
    {
        const std::string vertexPath = resourcePath + ".vert";
        const std::string fragPath = resourcePath + ".frag";

        std::string vertexContent;
        std::string fragContent;

        Shader* shader = new Shader(vertexPath.c_str(), fragPath.c_str());

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
#endif //FORGE_DEBUG_ENABLED
}