#pragma once

#include "engine/core/Object.h"

namespace ForgeEngine
{
	enum class EInitializationState
	{
		NeedsPreInit,
		NeedsInit,
		NeedsPostInit,
		Initialized
	};

	class ManagedObject : public Object
	{
		using Mother = Object;

		friend class World;

        public:
            ManagedObject();

            void SetActive(bool active);
            bool IsActive() const { return m_IsActive; }

            EInitializationState GetInitializationState() const { return m_InitializationState; }
            bool NeedsPreInit() const { return m_InitializationState == EInitializationState::NeedsPreInit; }
            bool NeedsInit() const { return m_InitializationState == EInitializationState::NeedsInit; }
            bool NeedsPostInit() const { return m_InitializationState == EInitializationState::NeedsPostInit; }
            bool IsInitialized() const { return m_InitializationState == EInitializationState::Initialized; }

            void Destroy() { OnDestroy(); }

        protected:
            virtual void OnActivate() {}
            virtual void OnDeactivate() {}

            virtual bool OnPreInit() { m_InitializationState = EInitializationState::NeedsInit;  return true; }
            virtual bool OnInit() { m_InitializationState = EInitializationState::NeedsPostInit;  return true; }
            virtual bool OnPostInit() { m_InitializationState = EInitializationState::Initialized;  return true; }

            virtual void OnPreUpdate(float dT) {}
            virtual void OnUpdate(float dT) {}
            virtual void OnPostUpdate(float dT) {}

    #ifdef FORGE_DEBUG_ENABLED
            virtual void OnDrawDebug(float dT) const {}
    #endif //FORGE_DEBUG_ENABLED

        virtual void OnDestroy() {}

		private:
			bool m_IsActive{ true };
			EInitializationState m_InitializationState{ EInitializationState::NeedsPreInit };
	};
}