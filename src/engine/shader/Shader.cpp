#include "Shader.h"

#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/Material.h"
#include "engine/shader/ShaderUtils.h"
#include "system/io/FileUtils.h"
#include "system/misc/Color.h"
#include "system/misc/Utils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <numeric>
#include <sstream>

namespace ForgeEngine
{
	Shader::Shader(const std::string& vsPath, const std::string& fsPath)
	{
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

        std::string vertexContent;
        std::string fragContent;

        if (FileUtils::TryLoadFileContent(vsPath, vertexContent) && FileUtils::TryLoadFileContent(fsPath, fragContent))
        {
            std::vector<std::string> extractedLines = ForgeUtils::ExtractLines(GLSL_ATTRIBUTE_TOKEN, vertexContent);
            for (const std::string& str : extractedLines)
            {
                std::vector<std::string> splitted = ForgeUtils::Split(" ", str);
                if (splitted.size() == 2)
                {
                    m_AttributesSizes.push_back(std::stoi(splitted[1]));
                }
            }

            if (!ShaderUtils::TryCompileShader(m_VertexID, vsPath.c_str(), vertexContent.c_str(), GL_VERTEX_SHADER) ||
                !ShaderUtils::TryCompileShader(m_FragmentID, fsPath.c_str(), fragContent.c_str(), GL_FRAGMENT_SHADER) ||
                !ShaderUtils::TryLinkShaderProgram(m_ProgramID, true, &m_VertexID, &m_FragmentID))
            {
                std::cout << "Could not compile shaders!" << std::endl;
            }
        }
	}

	Shader::~Shader()
	{
		ShaderUtils::DeleteShaders(&m_VertexID, &m_FragmentID);
		ShaderUtils::DeletePrograms(&m_ProgramID);
	}

	void Shader::Use() const
	{
		glUseProgram(m_ProgramID);
	}

	int Shader::GetInputDataSize() const
	{
		if (m_InputDataSize == -1)
		{
			m_InputDataSize = std::accumulate(m_AttributesSizes.begin(), m_AttributesSizes.end(), 0);
		}
		return m_InputDataSize;
	}

	unsigned int Shader::GetAttributeSize(int index) const
	{
		if (index < m_AttributesSizes.size())
		{
			return m_AttributesSizes[index];
		}
		return -1;
	}

	void Shader::SetFloat(const char* which, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ProgramID, which), value);
	}

	void Shader::SetBool(const char* which, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, which), static_cast<int>(value));
	}

	void Shader::SetInt(const char* which, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, which), value);
	}

	void Shader::SetColor(const char* which, const Color& value) const
	{
		glUniform4f(glGetUniformLocation(m_ProgramID, which), value.GetRRatio(), value.GetGRatio(), value.GetBRatio(), value.GetA());
	}

	void Shader::SetTexture(unsigned int which, const Texture* texture) const
	{
        SetBool(DEFAULT_USE_TEXTURE_NAME, texture != nullptr);
        glActiveTexture(texture != nullptr ? which : 0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture != nullptr ? texture->GetGLTexture() : 0);
	}

	void Shader::SetMatrix4(const char* which, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, which), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetMatrix3(const char* which, const glm::mat3& matrix) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, which), 1, GL_FALSE, glm::value_ptr(matrix));
	}

    void Shader::SetVector4(const char* which, const Vector3& vector) const
    {
        glUniform4f(glGetUniformLocation(m_ProgramID, which), vector.x, vector.y, vector.z, 0.f);
    }

    void Shader::SetMaterial(const Material& material) const
    {
        SetColor(DEFAULT_MATERIAL_COLOR_NAME, material.GetColor());
        SetFloat(DEFAULT_MATERIAL_DIFFUSE_NAME, material.GetDiffuse());
        SetFloat(DEFAULT_MATERIAL_SPECULAR_NAME, material.GetSpecular());
        SetInt(DEFAULT_MATERIAL_SHININESS_NAME,material.GetShininess());
        SetTexture(GL_TEXTURE0, material.GetTexture());
    }

#ifdef FORGE_DEBUG_ENABLED
    void Shader::OnDrawDebug() const
    {
        ImGui::Text("Input Data Size: %d", GetInputDataSize());
    }
#endif //FORGE_DEBUG_ENABLED
}