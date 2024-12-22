#pragma once

#include "engine/components/Component.h"

#include <memory>
#include <string>

namespace ForgeEngine
{
    class Animation;

    class AnimatorComponent : public Component
    {
        using Mother = Component;

    public:
        AnimatorComponent(const std::string& animatorPath);

#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "AnimatorComponent"; }
#endif //FORGE_DEBUG_ENABLED

    protected:
        bool OnInit() override;

#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug(float dT) const override;
#endif //FORGE_DEBUG_ENABLED

    private:
        std::string m_AnimatorPath;
        std::shared_ptr<Animation> m_Animation;
    };
}
#pragma once
