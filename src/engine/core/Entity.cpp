#include "Entity.h"

#include "engine/core/World.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <algorithm>

namespace ForgeEngine
{
    Entity::Entity(World& world, const std::string& debugName)
        : m_World(world)
#ifdef FORGE_DEBUG_ENABLED
        , m_DebugName(debugName)
#endif //FORGE_DEBUG_ENABLED
    {
    }

    bool Entity::OnPreInit() /*override*/
    {
        bool success = Mother::OnPreInit();
        for (auto& component : m_RegisteredComponents)
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
        return success;
    }

    bool Entity::OnInit() /*override*/
    {
        bool success = Mother::OnInit();
        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (!component->OnInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
        return success;
    }

    void Entity::OnUpdatePreRender(float dT) /*override*/
    {
#ifdef FORGE_DEBUG_ENABLED
        if (m_DestroyRequested)
        {
            Destroy();
            return;
        }
#endif
        if (!IsActive())
        {
            return;
        }

        Mother::OnUpdatePreRender(dT);

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (component->IsInitialized())
                {
                    component->OnUpdatePreRender(dT);
                }
                else if (component->NeedsPreInit())
                {
                    component->OnPreInit();
                }
            }
        }
    }

    void Entity::OnUpdate(float dT) /*override*/
    {
        if (!IsActive())
        {
            return;
        }

        Mother::OnUpdate(dT);

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (component->IsInitialized())
                {
                    component->OnUpdate(dT);
                }
                else if (component->NeedsInit())
                {
                    component->OnInit();
                }
            }
        }
    }

    void Entity::OnUpdatePostRender(float dT) /*override*/
    {
        if (!IsActive())
        {
            return;
        }

        Mother::OnUpdatePostRender(dT);

        m_Transform.Update();

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (component->IsInitialized())
                {
                    component->OnUpdatePostRender(dT);
                }
            }
        }
    }
#ifdef FORGE_DEBUG_ENABLED
    void Entity::OnDrawDebug(float dT) const  /*override*/
    {
        ImGuiUtils::PushId((int)this);
        Mother::OnDrawDebug(dT);
        if (ImGui::Button("Destroy"))
        {
            m_DestroyRequested = true;
        }
        m_Transform.DebugImGUI();
        m_Transform.Draw();

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr)
            {
                if (ImGui::CollapsingHeader(component->GetDebugName()))
                {
                    ImGui::Indent();
                    if (component->IsInitialized())
                    {
                        component->OnDrawDebug(dT);
                    }
                    ImGui::Unindent();
                }
            }
        }
        ImGui::PopID();
    }
#endif //FORGE_DEBUG_ENABLED

    void Entity::OnDestroy() /*override*/
    {
        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr)
            {
                component->Destroy();
            }
        }
        Mother::OnDestroy();
        m_World.UnregisterEntity(this);
    }
}