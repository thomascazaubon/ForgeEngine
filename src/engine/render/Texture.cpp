#include "Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <iostream>
#include <stb_image/stb_image.h>

namespace ForgeEngine
{
    Texture::Texture(const std::string& texturePath) 
        : Mother(texturePath)
    {
#ifdef FORGE_DEBUG_ENABLED
        m_DebugName = texturePath;
#endif //FORGE_DEBUG_ENABLED

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texturePath.c_str(), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        stbi_set_flip_vertically_on_load(false);

        if (data)
        {
            glGenTextures(1, &m_GLTexture);
            glBindTexture(GL_TEXTURE_2D, m_GLTexture);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
#ifdef FORGE_DEBUG_ENABLED
            DebugUtils::LogError("Texture {}: Cannot load texture.", texturePath.c_str());
#endif //FORGE_DEBUG_ENABLED
        }
        
        stbi_image_free(data);
    }

    Texture::Texture(void* data, unsigned int width, unsigned int height) :
        Mother(""),
        m_Width(width),
        m_Height(height)
    {
        if (data)
        {
            glGenTextures(1, &m_GLTexture);
            glBindTexture(GL_TEXTURE_2D, m_GLTexture);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_GLTexture);
    }

    void Texture::Use()
    {
        glBindTexture(GL_TEXTURE_2D, m_GLTexture);
    }

#ifdef FORGE_DEBUG_ENABLED
    void Texture::OnDrawDebug() const
    {
        ImGui::Text("Width: %d", m_Width);
        ImGui::Text("Height: %d", m_Height);
        ImGui::Text("Channels: %d", m_Channels);
    }
#endif //FORGE_DEBUG_ENABLED
}