#include "engine/core/World.h"

#include "engine/core/Entity.h"
#include "engine/worldcomponents/DebugManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <algorithm>
#include <string>

namespace ForgeEngine
{
    //TODO: Return weakptr
    Entity* World::RegisterEntity(const char* debugName /*= nullptr*/)
    {
        std::string finalDebugName{ debugName != nullptr ? debugName : "" };
#ifdef FORGE_DEBUG_ENABLED
        if (debugName == nullptr)
        {
            finalDebugName = "Entity" + std::to_string(m_LastCreatedEntityId);
            m_LastCreatedEntityId++;
        }
#endif //FORGE_DEBUG_ENABLED

        Entity* entity = new Entity(*this, finalDebugName);
        m_RegisteredEntities.push_back(std::unique_ptr<Entity>(entity));
        return entity;
    }

    void World::UnregisterEntity(const Entity* entity)
    {
        if (entity != nullptr)
        {
            for (unsigned int i = 0; i < m_RegisteredEntities.size(); i++)
            {
                if (m_RegisteredEntities[i].get() == entity)
                { 
                    m_RegisteredEntities.erase(m_RegisteredEntities.begin() + i);
                }
            }
        }
    }

    World::~World()
    {
        OnDestroy();
    }

    bool World::PreInit()
    {
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                entity->OnPreInit();
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                if (!component->OnPreInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
        return true;
    }

    bool World::Init()
    {
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                entity->OnInit();
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                if (!component->OnInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
        return true;
    }

    bool World::PostInit()
    {
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                entity->OnPostInit();
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                if (!component->OnPostInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
        return true;
    }

    void World::PreUpdate(float dT)
    {
        unsigned int initializedEntitiesThisFrame = 0;
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                if (entity->IsInitialized())
                {
                    entity->OnPreUpdate(dT);
                }
                else if (entity->NeedsPreInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
                {
                    entity->OnPreInit();
                    initializedEntitiesThisFrame++;
                }
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnPreUpdate(dT);
            }
        }
    }

    void World::Update(float dT)
    {
        unsigned int initializedEntitiesThisFrame = 0;
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                if (entity->IsInitialized())
                {
                    entity->OnUpdate(dT);
                }
                else if (entity->NeedsInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
                {
                    entity->OnInit();
                    initializedEntitiesThisFrame++;
                }
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnUpdate(dT);
            }
        }
    }

    void World::PostUpdate(float dT)
    {
        unsigned int initializedEntitiesThisFrame = 0;
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                if (entity->IsInitialized())
                {
                    entity->OnPostUpdate(dT);
                }
                else if (entity->NeedsPostInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
                {
                    entity->OnPostInit();
                    initializedEntitiesThisFrame++;
                }
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnPostUpdate(dT);
            }
        }
    }
#ifdef FORGE_DEBUG_ENABLED
    void World::DrawDebug(float dT) 
    {
        const DebugManager* debugManager = GetComponentByType<const DebugManager>();
        if (debugManager && debugManager->IsImGUIEnabled())
        {
            ImGui::Begin("World");
            {
                static bool showDemo = false;
                ImGui::Checkbox("Show Demo", &showDemo);
                if (showDemo)
                {
                    ImGui::ShowDemoWindow();
                }

                if (ImGui::CollapsingHeader("Components"))
                {
                    ImGui::Indent();
                    {
                        for (auto& component : m_Components)
                        {
                            if (component != nullptr)
                            {
                                if (ImGui::CollapsingHeader(component->GetDebugName()))
                                {
                                    ImGui::Indent();
                                    {
                                        component->OnDrawDebug(dT);
                                    }
                                    ImGui::Unindent();
                                }
                            }
                        }
                    }
                    ImGui::Unindent();
                }
                if (ImGui::CollapsingHeader("Entities"))
                {
                    ImGui::Indent();
                    {
                        for (auto& entity : m_RegisteredEntities)
                        {
                            if (entity != nullptr)
                            {
                                if (ImGui::CollapsingHeader(entity->GetDebugName()))
                                {
                                    ImGui::Indent();
                                    {
                                        if (entity->IsInitialized())
                                        {
                                            entity->OnDrawDebug(dT);
                                        }
                                    }
                                    ImGui::Unindent();
                                }
                            }
                        }
                    }
                    ImGui::Unindent();
                }
            }
            ImGui::End();
        }
    }
#endif

    void World::OnDestroy()
    {
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                entity->Destroy();
            }
        }
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->Destroy();
            }
        }
    }
}