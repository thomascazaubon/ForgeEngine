#pragma once

#include "engine/assetloaders/LoadableAsset.h"
#include "engine/time/Timer.h"

#include <memory>
#include <string>
#include <vector>

namespace ForgeEngine
{
    class Texture;

    class Animation : public LoadableAsset
    {
        friend class AnimationLoader;

    public:
        //TODO: fix this
#ifdef FORGE_DEBUG_ENABLED
        const char* GetDebugName() const override { return "?"; }
#endif //FORGE_DEBUG_ENABLED

        bool IsValid() const override { return true; }

    private:
        Animation(const std::string& source
#ifdef FORGE_DEBUG_ENABLED
            , const char* path
#endif //FORGE_DEBUG_ENABLED
        );

        bool ResolveAttribute(const std::string& name, const std::string& value);

#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED
        Timer m_Timer;
        std::vector<std::shared_ptr<Texture>> m_Frames;
        float m_Duration{0.f};
    };
}