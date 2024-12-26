#pragma once

#include "engine/assetloaders/LoadableAsset.h"

#include <unordered_map>
#include <memory>
#include <vector>

namespace ForgeEngine
{
    class Animation2D;

    class Animator2D : public LoadableAsset
    {
        using Mother = LoadableAsset;

        template<typename T>
        friend class AssetLoader;

        public:
            bool IsValid() const override { return !m_Animations.empty(); }
            const std::string& GetDefaultAnimationName() const { return m_Animations.begin()->first; }
            const Animation2D* GetAnimation(const std::string& name) const;
            bool HasAnimation(const std::string& name) const;

#ifdef FORGE_DEBUG_ENABLED
            std::vector<std::string> GetStates() const;
#endif //FORGE_DEBUG_ENABLED

        private:
            Animator2D(const std::string& path);

    #ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const override;
    #endif //FORGE_DEBUG_ENABLED

            std::unordered_map<std::string, std::shared_ptr<Animation2D>> m_Animations;
    };
}