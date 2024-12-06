#pragma once

#include "engine/components/Component.h"

namespace ForgeEngine
{
	class CameraComponent;

	class FirstPersonControllerComponent : public Component
	{
		using Mother = Component;

	public:
		FirstPersonControllerComponent(float moveSpeed = 10.f, float rotationSpeed = 10.f);

		virtual bool OnInit() override;
		virtual void OnUpdate(float dT) override;
		virtual void OnDestroy() override;

#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug(float dT) const override;

        const char* GetDebugName() const override { return "FirstPersonControllerComponent"; }
#endif //FORGE_DEBUG_ENABLED

    private:
        float m_MoveSpeed{10.f};
        float m_RotationSpeed{10.f};

        CameraComponent* m_CameraComponent{};
	};
}