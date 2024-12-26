#pragma once

#include "engine/components/Component.h"

namespace ForgeEngine
{
    class Animator2DComponent;

    class NPCComponent : public Component
    {
        using Mother = Component;

        public:
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "NPCComponent"; }
#endif //FORGE_DEBUG_ENABLED

        protected:
            bool OnInit() override;
            void OnUpdate(float dT) override;

        private:
            Animator2DComponent* m_AnimatorComponent{ nullptr };
    };
}
#pragma once
