#include "LoadableAsset.h"

namespace ForgeEngine
{
    LoadableAsset::LoadableAsset(const std::string& path)
#ifdef FORGE_DEBUG_ENABLED
        : m_DebugName(path)
#endif
    {
    }
}

