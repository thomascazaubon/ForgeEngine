#include "Animation.h"

#include "engine/io/FileUtils.h"
#include "engine/render/Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    Animation::Animation(const std::string& source
#ifdef FORGE_DEBUG_ENABLED
        , const char* path
#endif //FORGE_DEBUG_ENABLED
    )
    {
        std::vector<std::string> lines = FileUtils::Split("\n", source);
        for (const std::string& line : lines)
        {
            const std::vector<std::string> splittedLine = FileUtils::Split(":", line);
            if (splittedLine.size() == 2)
            {
                if (!ResolveAttribute(splittedLine[0], splittedLine[1]))
                {
#ifdef FORGE_DEBUG_ENABLED
                    DebugUtils::LogError("AnimationLoader: Cannot resolve attribute \"{}\" in \"{}\"", splittedLine[0], path);
#endif //FORGE_DEBUG_ENABLED
                }
            }
            else if (splittedLine.size() == 0)
            {
                //Resolve brackets
            }
            else
            {
                DebugUtils::LogError("error");
            }
        }
    }

    bool Animation::ResolveAttribute(const std::string& name, const std::string& value)
    {
        if (name == "duration")
        {
            m_Duration = stof(value);
            return true;
        }

        return false;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Animation::OnDrawDebug() const
    {
        
    }
#endif //FORGE_DEBUG_ENABLED
}
