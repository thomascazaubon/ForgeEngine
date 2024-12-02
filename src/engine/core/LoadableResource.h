#pragma once

#include "engine/core/Object.h"

namespace ForgeEngine
{
    class LoadableResource : public Object
    {
        public:
            virtual bool IsValid() const = 0;
#ifdef FORGE_DEBUG_ENABLED
            virtual void OnDrawDebug() const {}
#endif //FORGE_DEBUG_ENABLED
    };
}
