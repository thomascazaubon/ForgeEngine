#include "Shader.h"

#include "engine/core/ForgeEngine.h"
#include "engine/io/FileUtils.h"
#include "engine/render/Color.h"
#include "engine/render/Material.h"
#include "engine/render/ShaderUtils.h"
#include "engine/render/Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <algorithm>
#include <fstream>
#include <format>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <numeric>
#include <sstream>

namespace ForgeEngine
{
	namespace Private
	{
#ifdef FORGE_DEBUG_ENABLED
		ImVec4 GetUniformTypeColor(const std::string& type)
		{
			if (type == "bool")
			{
				return ImGUIUtils::ToImColor(COLOR_BLUE);
			}
			if (type == "float")
			{
				return ImGUIUtils::ToImColor(COLOR_GREEN);
			}
			if (type == "vec3")
			{
				return ImGUIUtils::ToImColor(COLOR_PURPLE);
			}
			return ImGUIUtils::ToImColor(COLOR_ORANGE);
			
		}
#endif //FORGE_DEBUG_ENABLED
	}

	Shader::Shader(const std::string& shaderPath)
	{
		const std::string vsPath = shaderPath + ".vert";
		std::string gsPath = shaderPath + ".geom";
		const std::string fsPath = shaderPath + ".frag";

		std::ifstream vertexShaderFile;
		std::ifstream geometryShaderFile;
		std::ifstream fragmentShaderFile;

		std::stringstream vertexShaderStream;
		std::stringstream geometryShaderStream;
		std::stringstream fragmentShaderStream;

        std::string vertexContent;
        std::string geomContent;
        std::string fragContent;

		const bool hasGeometryShaderPath = FileUtils::TryLoadFileContent(gsPath, geomContent);

        if (FileUtils::TryLoadFileContent(vsPath, vertexContent) && FileUtils::TryLoadFileContent(fsPath, fragContent))
        {
            std::vector<std::string> extractedLines = FileUtils::ExtractLines(GLSL_ATTRIBUTE_TOKEN, vertexContent);
            for (const std::string& str : extractedLines)
            {
                std::vector<std::string> splitted = FileUtils::Split(" ", str);
                if (splitted.size() == 2)
                {
                    m_AttributesSizes.push_back(std::stoi(splitted[1]));
                }
            }

			std::string vsLogs;
			const bool vertexCompiled = ShaderUtils::TryCompileShader(m_VertexID, vertexContent.c_str(), GL_VERTEX_SHADER, vsLogs);
			std::string gsLogs;
			const bool geometryCompiled = hasGeometryShaderPath ? ShaderUtils::TryCompileShader(m_GeometryID, geomContent.c_str(), GL_GEOMETRY_SHADER, gsLogs) : true;
			std::string fsLogs;
			const bool fragmentCompiled = ShaderUtils::TryCompileShader(m_FragmentID, fragContent.c_str(), GL_FRAGMENT_SHADER, fsLogs);
			std::string linkageLogs;
			const bool programCompiled = ShaderUtils::TryLinkShaderProgram(m_ProgramID, linkageLogs, m_VertexID, m_GeometryID, m_FragmentID);

#ifdef FORGE_DEBUG_ENABLED
			if (vertexCompiled && geometryCompiled && fragmentCompiled && programCompiled)
			{
				ParseUniforms(vertexContent);
				ParseUniforms(geomContent);
				ParseUniforms(fragContent);
				OrderUniforms();
			}
			else
			{
				if (!vertexCompiled)
				{
					DebugUtils::LogError("Could not compile shader {}:\n{}", vsPath.c_str(), vsLogs.c_str());
				}
				if (!geometryCompiled)
				{
					DebugUtils::LogError("Could not compile shader {}:\n{}", gsPath.c_str(), gsLogs.c_str());
				}
				if (!fragmentCompiled)
				{
					DebugUtils::LogError("Could not compile shader {}:\n{}", fsPath.c_str(), fsLogs.c_str());
				}
				if (vertexCompiled && geometryCompiled && fragmentCompiled && !programCompiled)
				{
					DebugUtils::LogError("Could not link shaders {}:\n{}", shaderPath.c_str(), linkageLogs.c_str());
				}
			}
#endif //FORGE_DEBUG_ENABLED
        }
	}

	Shader::~Shader()
	{
		ShaderUtils::DeleteShaders(m_VertexID, m_GeometryID, m_FragmentID);
		ShaderUtils::DeletePrograms(m_ProgramID);
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

    void Shader::SetVector3(const char* which, const Vector3& vector) const
    {
        glUniform3f(glGetUniformLocation(m_ProgramID, which), vector.x, vector.y, vector.z);
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
	void Shader::ParseUniforms(const std::string& fileContent)
	{
		for (const std::string& str : FileUtils::ExtractLines(GLSL_UNIFORM_TOKEN, fileContent))
		{
			std::vector<std::string> splitted = FileUtils::Split(" ", str);
			if (splitted.size() == 3)
			{
				const std::string name = FileUtils::Split(";", splitted[2])[0];
				if (GetUniformData(name) == nullptr)
				{
					UniformData data;
					data.m_VariableName = name;
					data.m_VariableType = splitted[1].c_str();
					m_UniformsData.push_back(data);
				}
			}
		}
	}

	const Shader::UniformData* Shader::GetUniformData(const std::string& uniformName) const
	{
		for (const UniformData& data : m_UniformsData)
		{
			if (data.m_VariableName == uniformName)
			{
				return &data;
			}
		}
		return nullptr;
	}

	void Shader::OrderUniforms()
	{
		std::sort(m_UniformsData.begin(), m_UniformsData.end(), [&](const UniformData& a, const UniformData& b)
			{
				return (a.m_VariableName < b.m_VariableName);
			});
	}

    void Shader::OnDrawDebug() const
    {
        ImGui::Text("Program ID: %d", m_ProgramID);
        ImGui::Text("Input Data Size: %d", GetInputDataSize());
        ImGui::Text("Vertex ID: %d", m_VertexID);
        ImGui::Text("Geometry ID: %d", m_GeometryID);
        ImGui::Text("FragmentID ID: %d", m_FragmentID);

		for (const UniformData& data : m_UniformsData)
		{
			ImGui::TextColored(Private::GetUniformTypeColor(data.m_VariableType), "%s (%s)", data.m_VariableName.c_str(), data.m_VariableType.c_str());
		}
    }
#endif //FORGE_DEBUG_ENABLED
}