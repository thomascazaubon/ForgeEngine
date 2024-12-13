#pragma once

#include "engine/render/OpenGL.h"

#include <string>

namespace ForgeEngine
{
	class Color;

	namespace ShaderUtils
	{
		#define LOG_SIZE 512

		bool TryCompileShader(unsigned int& shader, const char* shaderSource, int shaderType, std::string& logs);
		void ClearScreen(Color backgroundColor);

		template<typename... ShaderIds>
			requires ((std::same_as<ShaderIds, unsigned int> && ...))
		bool TryLinkShaderProgram(unsigned int& shaderProgram, std::string& logs, ShaderIds... ids)
		{
			//Creates shader program
			shaderProgram = glCreateProgram();

			//Links all shaders into the shaderProgram
			for (const unsigned int id : { ids...}) 
			{
				glAttachShader(shaderProgram, id);
			}

			glLinkProgram(shaderProgram);
			//Check if linkage was successful
			int compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationSuccess);

			if (!compilationSuccess)
			{
				glGetProgramInfoLog(shaderProgram, LOG_SIZE, nullptr, infoLog);
				logs = infoLog;
			}

			return static_cast<bool>(compilationSuccess);
		}

		template<typename... ShaderIds>
			requires ((std::same_as<ShaderIds, unsigned int> && ...))
		void DeleteShaders(ShaderIds... ids)
		{
			for (const unsigned int id : { ids...}) 
			{
				glDeleteShader(id);
			}
		}

		template<typename... ProgramIds>
			requires ((std::same_as<ProgramIds, unsigned int> && ...))
		void DeletePrograms(ProgramIds... ids)
		{
			for (const unsigned int id : { ids...}) 
			{
				glDeleteProgram(id);
			}
		}
	}
}