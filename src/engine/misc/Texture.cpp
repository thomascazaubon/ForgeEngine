#include "Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <iostream>

#include <stb_image/stb_image.h>

namespace ForgeEngine
{
	Texture::Texture(const std::string& texturePath, unsigned int rgbaMode/*= GL_RGB*/, bool flip/* = true*/) 
        : Mother()
        , m_Name(texturePath)
	{
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(texturePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
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

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, rgbaMode, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Could not load texture " << texturePath << "." << std::endl;
		}
		
		stbi_image_free(data);
	}

	Texture::Texture(void* data, unsigned int width, unsigned int height) :
		Mother(),
		m_Width(width),
		m_Height(height)
	{
		if (data)
		{
			glGenTextures(1, &m_GLTexture);
			glBindTexture(GL_TEXTURE_2D, m_GLTexture);

			// set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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