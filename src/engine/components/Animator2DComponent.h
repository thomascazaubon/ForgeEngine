#pragma once

#include "engine/components/Component.h"
#include "engine/time/Timer.h"

#include <memory>
#include <string>

namespace ForgeEngine
{
    class Animation2D;
    class Animator2D;
    class Texture;

    class Animator2DComponent : public Component
    {
        using Mother = Component;

        public:
            Animator2DComponent(const std::string& animatorPath);

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "AnimatorComponent"; }
#endif //FORGE_DEBUG_ENABLED

            const Texture& GetCurrentTexture() const;
            const Animation2D& GetCurrentAnimation() const;

            bool SetRunningAnimation(const std::string& name);

        protected:
            void OnUpdate(float dT) override;
            bool OnInit() override;

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug(float dT) const override;
#endif //FORGE_DEBUG_ENABLED

        private:
            void RestartTimer();

            Timer m_Timer;

            std::string m_CurrentAnimation;
            std::string m_AnimatorPath;
            std::shared_ptr<Animator2D> m_Animator;
    };
}
#pragma once
