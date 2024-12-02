#include "Entity.h"

#include "engine/components/TransformComponent.h"
#include "system/math/Vector3.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <algorithm>

namespace ForgeEngine
{
    Entity::Entity(World& world, TransformComponent* transform, const std::string& debugName)
        : m_World(world)
        , m_Transform(*transform)
#ifdef FORGE_DEBUG_ENABLED
        , m_DebugName(debugName)
#endif //FORGE_DEBUG_ENABLED
    {
        m_RegisteredComponents.push_back(std::unique_ptr<TransformComponent>(transform));
    }

    const Vector3& Entity::GetPosition() const
    {
        return GetTransform().GetPosition(); 
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

        ImGui::PushID(GetID());
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