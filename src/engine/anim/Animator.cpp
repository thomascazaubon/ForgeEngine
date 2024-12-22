#include "Animator.h"

#include "engine/assetloaders/AnimationLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/io/FileUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    Animator::Animator(const std::string& path)
        : Mother(path)
    {
        std::string source;
        if (FileUtils::TryLoadFileContent(path, source))
        {
            const std::vector<std::string> lines = FileUtils::Split("\n", source);
            for (unsigned int i = 0; i < lines.size(); i++)
            {
                const std::string& line = lines[i];
                std::vector<std::string> splittedLine = FileUtils::Split(":", line);
                if (splittedLine.size() == 2)
                {
                    if (const std::shared_ptr<Animation>* animation = GameHandler::Get().GetWorld().GetComponentByType<AnimationLoader>()->GetOrLoadResource(splittedLine[1]))
                    {
                        m_Animations[splittedLine[0]] = *animation;
                    }
                    else
                    {
                        DebugUtils::LogError("AnimatorLoader: Cannot load animation \"{}\" in {} (line {}).", splittedLine[1], path, i + 1);
                    }
                }
            }
        }
    }

    bool Animator::HasAnimation(const std::string& name) const
    {
        return GetAnimation(name) != nullptr;
    }

    const Animation* Animator::GetAnimation(const std::string& name) const
    {
        auto it = m_Animations.find(name);
        return (it != m_Animations.end()) ? (*it).second.get() : nullptr;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Animator::OnDrawDebug() const
    {
        for (auto pair : m_Animations)
        {
            ImGui::Text("%s: %s", pair.first.c_str(), pair.second.get()->GetDebugName());
        }
    }
#endif //FORGE_DEBUG_ENABLED
}
