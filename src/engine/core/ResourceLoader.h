#pragma once

#include "engine/core/WorldComponent.h"
#include "system/io/FileUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <memory>
#include <string>
#include <unordered_map>

namespace ForgeEngine
{
    template <typename T>
    class ResourceLoader : public WorldComponent
    {
        using Mother = WorldComponent;
#define DEFAULT_RESOURCE_NAME "_default"

    public:
        const std::shared_ptr<T>* GetOrLoadResource(const std::string& resourcePath)
        {
            const std::shared_ptr<T>* resource = GetResource(resourcePath);

            if (!IsResourceLoaded(resourcePath))
            {
                if (resourcePath != DEFAULT_RESOURCE_NAME)
                {
                    if (!AddResource(resourcePath))
                    {
                        return GetDefault();
                    }
                }
                else
                {
                    AddResource(resourcePath);
                }
            }

            return GetResource(resourcePath);
        }

        const std::shared_ptr<T>* GetDefault()
        {
            return GetOrLoadResource(DEFAULT_RESOURCE_NAME);
        }

        void OnPostUpdate(float dT) override
        {
            Mother::OnPostUpdate(dT);

            for (auto it = m_LoadedResources.begin(); it != m_LoadedResources.end();) 
            {
                if ((*it).second.use_count() == 1)
                {
                    it = m_LoadedResources.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug(float dT) const override
        {
            Mother::OnDrawDebug(dT);
            for (const Resource& resource : m_LoadedResources)
            {
                std::string resourceHeader = resource.first + " [" + std::to_string(resource.second.use_count() - 1) + "]";
                if (ImGui::CollapsingHeader(resourceHeader.c_str()))
                {
                    DebugResource(*resource.second.get());
                }
            }
        }
#endif //FORGE_DEBUG_ENABLED

        protected:
            virtual bool AddResource(const std::string& resourcePath) = 0;

#ifdef FORGE_DEBUG_ENABLED
            virtual void DebugResource(const T& resource) const = 0;
#endif //FORGE_DEBUG_ENABLED

            bool IsResourceLoaded(const std::string& resourcePath)
            {
                auto it = m_LoadedResources.find(resourcePath);
                return (it != m_LoadedResources.end()) ? true : false;
            }

            const std::shared_ptr<T>* GetResource(const std::string& resourcePath)
            {
                auto it = m_LoadedResources.find(resourcePath);
                return (it != m_LoadedResources.end()) ? &((*it).second) : nullptr;
            }

            using Resource = std::pair<const std::string&, const std::shared_ptr<T>&>;
            std::unordered_map<std::string, std::shared_ptr<T>> m_LoadedResources{};
    };
}