#include "Material.h"

#include "engine/assetloaders/TextureLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/io/FileUtils.h"
#include "engine/render/Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <vector>

namespace ForgeEngine
{
    Material::Material(const std::string& source
#ifdef FORGE_DEBUG_ENABLED
        , const char* path
#endif //FORGE_DEBUG_ENABLED
    )
    {
        std::vector<std::string> attributes = FileUtils::Split("\n", source);

        if (!source.empty())
        {
            for (const std::string& attribute : attributes)
            {
                std::vector<std::string> splittedAttribute = FileUtils::Split(":", attribute);
                const std::string& name = splittedAttribute[0];

                if (splittedAttribute.size() == 2)
                {
                    if (!ResolveAttribute(name, splittedAttribute[1]))
                    {
#ifdef FORGE_DEBUG_ENABLED
                        DebugUtils::LogError("Material {}: Cannot resolve attribute \"{}\".", path, name.c_str());
#endif //FORGE_DEBUG_ENABLED
                    }
                }
                else
                {
#ifdef FORGE_DEBUG_ENABLED
                    DebugUtils::LogError("Material {}: Invalid syntax \"{}\".", path, name.c_str());
#endif //FORGE_DEBUG_ENABLED
                }
            }
        }
        else
        {
            m_Color = COLOR_MAGENTA;
        }
    }

    bool Material::ResolveAttribute(const std::string& name, const std::string& value)
    {
        bool success = true;

        if (name == "color")
        {
            std::vector<std::string> components = FileUtils::Split(";", value);
            if (components.size() == 4)
            {
                m_Color = Color(stoi(components[0]), stoi(components[1]), stoi(components[2]), stof(components[3]));
            }
            else
            {
                success = false;
            }
        }
        else if (name == "diffuse")
        {
            m_Diffuse = stof(value);
        }
        else if (name == "specular")
        {
            m_Specular = stof(value);
        }
        else if (name == "shininess")
        {
            m_Shininess = stoi(value);
        }
        else if (name == "texture")
        {
            if (const std::shared_ptr<Texture>* texture = GameHandler::Get().GetWorld().GetComponentByType<TextureLoader>()->GetOrLoadResource(value))
            {
                m_Texture = std::shared_ptr<Texture>(*(GameHandler::Get().GetWorld().GetComponentByType<TextureLoader>()->GetOrLoadResource(value)));
            }
        }
        else
        {
            success = false;
        }

        return success;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Material::OnDrawDebug() const
    {
        ImGui::Text("Diffuse: %.2f", m_Diffuse);
        ImGui::Text("Specular: %.2f", m_Specular);
        ImGui::Text("Shininess: %d", m_Shininess);
        ImGui::Text("Color: ");
        ImGui::SameLine();
        ImGui::ColorButton("Color##3c", ImGuiUtils::ToImColor(m_Color), 0, ImVec2(50, 15));
        if (m_Texture != nullptr)
        {
            ImGui::Text("Texture: %s", m_Texture->GetDebugName());
        }
    }
#endif //FORGE_DEBUG_ENABLED
}
