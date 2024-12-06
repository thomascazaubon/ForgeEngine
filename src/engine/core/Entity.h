#pragma once

#include "engine/components/Component.h"
#include "engine/core/ManagedObject.h"
#include "engine/math/Vector3.h"

#include <memory>
#include <vector>
#include <string>

namespace ForgeEngine
{
    class TransformComponent;
    class World;

	class Entity : public ManagedObject
	{
		friend class World;

		using Mother = ManagedObject;

		public:
            TransformComponent& GetTransform() { return m_Transform; }
            const TransformComponent& GetTransform() const { return m_Transform; }

            const Vector3& GetPosition() const;

            World& GetWorld() { return m_World; }
            const World& GetWorld() const { return m_World; }

			template <typename T>
			T* RegisterComponent(T* component)
			{
				if (dynamic_cast<Component*>(component))
				{
					m_RegisteredComponents.push_back(std::unique_ptr<Component>(component));
					component->SetOwner(this);
				}
				return component;
			}

			template <typename T>
			T* GetComponentByType() const
			{
				for (auto& registeredComponent : m_RegisteredComponents)
				{
					if (auto tComponent = dynamic_cast<T*>(registeredComponent.get()))
					{
						return tComponent;
					}
				}
				return nullptr;
			}

			template <typename T>
			bool GetComponent(T* component) const
			{
				component = nullptr;
				for (auto& registeredComponent : m_RegisteredComponents)
				{
					if (T* tComponent = dynamic_cast<T*>(registeredComponent.get()))
					{
						component = tComponent;
						return true;
					}
				}
				return false;
			}

#ifdef FORGE_DEBUG_ENABLED
        public:
            const char* GetDebugName() const override { return m_DebugName.c_str(); }
            virtual void OnDrawDebug(float dT) const override;
#endif //FORGE_DEBUG_ENABLED

		protected:
            Entity(World& world, TransformComponent* transform, const std::string& debugName);

			virtual bool OnPreInit() override;
			virtual bool OnInit() override;
			virtual bool OnPostInit() override;

			virtual void OnPreUpdate(float dT) override;
			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate(float dT) override;

			virtual void OnDestroy() override;

        private:
            World& m_World;
            TransformComponent& m_Transform;

            std::vector<std::unique_ptr<Component>> m_RegisteredComponents;

#ifdef FORGE_DEBUG_ENABLED
            const std::string m_DebugName;
#endif //FORGE_DEBUG_ENABLED
	};
}
