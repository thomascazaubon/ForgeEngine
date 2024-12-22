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
        using Mother = LoadableAsset;

        template<typename T>
        friend class AssetLoader;

        public:
            bool IsValid() const override { return !m_Frames.empty() && m_Duration > 0.f; }

            const Texture& GetFrameForProgressRatio(const float progressRatio) const;
            unsigned int GetFrameIndexForProgressRatio(const float progressRatio) const;
            float GetDuration() const { return m_Duration; }

        private:
            Animation(const std::string& path);

            bool ResolveAttribute(const std::string& name, const std::vector<std::string>& values
#ifdef FORGE_DEBUG_ENABLED
                , const std::string& path
#endif //FORGE_DEBUG_ENABLED
            );

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED

            std::vector<std::shared_ptr<Texture>> m_Frames;
            float m_Duration{0.f};
    };
}