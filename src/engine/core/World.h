#pragma once

#include "engine/core/ManagedObject.h"

#include "engine/core/Entity.h"
#include "engine/worldcomponents/WorldComponent.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
    class Entity;
    class GameHandler;
    class WorldComponent;

    class World : ManagedObject
    {
        friend class GameHandler;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        private:
            static const unsigned int K_MAX_INITIALIZATIONS_PER_FRAME = 1;

            std::vector<std::unique_ptr<Entity>> m_RegisteredEntities{};
            std::vector<std::unique_ptr<WorldComponent>> m_Components{};
            
        /************************************/
        /**************METHODS***************/
        /************************************/

        public:
            ~World();

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "Global Debug"; }
#endif //FORGE_DEBUG_ENABLED

            Entity* RegisterEntity(const char* debugName = nullptr);

            template <typename T>
            T* RegisterComponent(T* component)
            {
                if (dynamic_cast<WorldComponent*>(component))
                {
                    m_Components.push_back(std::unique_ptr<WorldComponent>(component));
                    component->SetWorld(this);
                }
                return component;
            }

            template <typename T>
            T* GetComponentByType() const
            {
                for (auto& registeredComponent : m_Components)
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
                for (auto& registeredComponent : m_Components)
                {
                    if (T * tComponent = dynamic_cast<T*>(registeredComponent.get()))
                    {
                        component = tComponent;
                        return true;
                    }
                }
                return false;
            }

        private:
            bool PreInit();
            bool Init();
            bool PostInit();

            void PreUpdate(float dT);
            void Update(float dT);
            void PostUpdate(float dT);

            void OnDestroy();

#ifdef FORGE_DEBUG_ENABLED
            void DrawDebug(float dT);

            unsigned int m_LastCreatedEntityId = 1;
#endif //FORGE_DEBUG_ENABLED
    };
}