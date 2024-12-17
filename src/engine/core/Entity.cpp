#include "Entity.h"

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

    bool Entity::OnPostInit() /*override*/
    {
        bool success = Mother::OnPostInit();
        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (!component->OnPostInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
        return success;
    }

    void Entity::OnPreUpdate(float dT) /*override*/
    {
        if (!IsActive())
        {
            return;
        }

        Mother::OnPreUpdate(dT);

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (component->IsInitialized())
                {
                    component->OnPreUpdate(dT);
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

    void Entity::OnPostUpdate(float dT) /*override*/
    {
        if (!IsActive())
        {
            return;
        }

        Mother::OnPostUpdate(dT);

        m_Transform.Update();

        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr && component->IsActive())
            {
                if (component->IsInitialized())
                {
                    component->OnPostUpdate(dT);
                }
                else if (component->NeedsPostInit())
                {
                    component->OnPostInit();
                }
            }
        }
    }
#ifdef FORGE_DEBUG_ENABLED
    void Entity::OnDrawDebug(float dT) const  /*override*/
    {
        Mother::OnDrawDebug(dT);

        m_Transform.DebugImGUI();
        m_Transform.Draw();

        ImGui::PushID(static_cast<int>(GetID()));
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
        Mother::OnDestroy();
        for (auto& component : m_RegisteredComponents)
        {
            if (component != nullptr)
            {
                component->Destroy();
            }
        }
    }
}