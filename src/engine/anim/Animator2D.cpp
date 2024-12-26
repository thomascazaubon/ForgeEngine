#include "Animator2D.h"

#include "engine/assetloaders/Animation2DLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/io/FileUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    Animator2D::Animator2D(const std::string& path)
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
                    if (const std::shared_ptr<Animation2D>* animation = GameHandler::Get().GetWorld().GetComponentByType<Animation2DLoader>()->GetOrLoadResource(splittedLine[1]))
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

    bool Animator2D::HasAnimation(const std::string& name) const
    {
        return GetAnimation(name) != nullptr;
    }

    const Animation2D* Animator2D::GetAnimation(const std::string& name) const
    {
        auto it = m_Animations.find(name);
        return (it != m_Animations.end()) ? (*it).second.get() : nullptr;
    }

#ifdef FORGE_DEBUG_ENABLED
    std::vector<std::string> Animator2D::GetStates() const
    {
        std::vector<std::string> states;

        for (auto pair : m_Animations)
        {
            states.push_back(pair.first);
        }

        return states;
    }

    void Animator2D::OnDrawDebug() const
    {
        for (auto pair : m_Animations)
        {
            ImGui::Text("%s: %s", pair.first.c_str(), pair.second.get()->GetDebugName());
        }
    }
#endif //FORGE_DEBUG_ENABLED
}
