#pragma once

#include "engine/core/Object.h"

#include <string>

namespace ForgeEngine
{
    class LoadableAsset : public Object
    {
        public:
            virtual bool IsValid() const = 0;
#ifdef FORGE_DEBUG_ENABLED
            virtual void OnDrawDebug() const {}
            const char* GetDebugName() const override { return m_DebugName.c_str(); }
#endif //FORGE_DEBUG_ENABLED
        protected:
            LoadableAsset(const std::string& path);

#ifdef FORGE_DEBUG_ENABLED
            std::string m_DebugName;
#endif //FORGE_DEBUG_ENABLED
    };
}
