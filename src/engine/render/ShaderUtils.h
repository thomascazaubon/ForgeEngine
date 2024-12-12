#pragma once

#include "engine/render/Shader.h"

namespace ForgeEngine
{
	class Color;

	namespace ShaderUtils
	{
		bool TryCompileShader(unsigned int& shader, const char* shaderSource, int shaderType, std::string& logs);
		bool TryLinkShaderProgram(unsigned int& shaderProgram, std::string& logs, const unsigned int* shaders, ...);
		void DeleteShaders(const unsigned int* shaders, ...);
		void DeletePrograms(const unsigned int* programs, ...);

		void ClearScreen(Color backgroundColor);
	}
}