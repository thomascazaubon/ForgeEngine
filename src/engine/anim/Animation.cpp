#include "Animation.h"

#include "engine/assetloaders/TextureLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/io/FileUtils.h"
#include "engine/render/Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    Animation::Animation(const std::string& path)
        : Mother(path)
    {
        std::string source;
        if (FileUtils::TryLoadFileContent(path, source))
        {
            const std::vector<std::string> lines = FileUtils::Split("\n", source);
            std::vector<std::string> gatheredAttributes;
#ifdef FORGE_DEBUG_ENABLED
            std::vector<std::string> errorLogs;
#endif //FORGE_DEBUG_ENABLED
            std::string bracketAttributeName = "";
            bool hasOpenedBracket = false;

            for (unsigned int i = 0; i < lines.size(); i++)
            {
                const std::vector<std::string> splittedLine = FileUtils::Split(":", lines[i]);
                if (splittedLine.size() == 2 && !hasOpenedBracket)
                {
                    gatheredAttributes.push_back(splittedLine[1]);
                    ResolveAttribute(splittedLine[0], gatheredAttributes
#ifdef FORGE_DEBUG_ENABLED
                        , path
#endif //FORGE_DEBUG_ENABLED
                    );
                }
                else if (splittedLine.size() == 1)
                {
                    if (!hasOpenedBracket && splittedLine[0] != "{" && lines[i + 1] == "{")
                    {
                        bracketAttributeName = splittedLine[0];
                        hasOpenedBracket = true;
                        gatheredAttributes.clear();
                        //We skip following bracket
                        i++;
                    }
                    else if (splittedLine[0] != "}" && hasOpenedBracket)
                    {
                        gatheredAttributes.push_back(splittedLine[0]);
                    }
                    else if (hasOpenedBracket && splittedLine[0] == "}")
                    {
                        ResolveAttribute(bracketAttributeName, gatheredAttributes
#ifdef FORGE_DEBUG_ENABLED
                            , path
#endif //FORGE_DEBUG_ENABLED
                        );
                        hasOpenedBracket = false;
                        gatheredAttributes.clear();
                        bracketAttributeName.clear();
                    }
                }
            }
        }
    }

    bool Animation::ResolveAttribute(const std::string& name, const std::vector<std::string>& values
#ifdef FORGE_DEBUG_ENABLED
        , const std::string& path
#endif //FORGE_DEBUG_ENABLED
    )
    {
        if (!values.empty())
        {
            if (name == "duration")
            {
                m_Duration = stof(values[0]);
                return true;
            }
            else if (name == "frames")
            {
                for (const std::string& value : values)
                {
                    if (const std::shared_ptr<Texture>* texture = GameHandler::Get().GetWorld().GetComponentByType<TextureLoader>()->GetOrLoadResource(value))
                    {
                        m_Frames.push_back(*texture);
                    }
#ifdef FORGE_DEBUG_ENABLED
                    else
                    {
                        DebugUtils::LogError("AnimationLoader: Cannot load texture \"{}\" in \"{}\"", value, path);
                    }
#endif //FORGE_DEBUG_ENABLED
                }

                return true;
            }
#ifdef FORGE_DEBUG_ENABLED
            else
            {
                DebugUtils::LogError("AnimationLoader: Cannot resolve attribute \"{}\" in \"{}\"", name, path);
            }
#endif //FORGE_DEBUG_ENABLED
        }

        return false;
    }

    const Texture* Animation::GetFrameForProgressRatio(const float progressRation) const
    {
        return nullptr;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Animation::OnDrawDebug() const
    {
        ImGui::Text("Duration: %.2f", m_Duration);
        ImGui::Text("Frames: %d", m_Frames.size());
    }
#endif //FORGE_DEBUG_ENABLED
}
