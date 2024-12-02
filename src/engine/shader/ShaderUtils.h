#pragma once

#include "engine/shader/Shader.h"

namespace ForgeEngine
{
	class Color;

	namespace ShaderUtils
	{
		bool TryCompileShader(unsigned int& shader, const char* shaderPath, const char* shaderSource, int shaderType, bool outputLogs = true);
		bool TryLinkShaderProgram(unsigned int& shaderProgram, bool outputLogs, const unsigned int* shaders, ...);
		void DeleteShaders(const unsigned int* shaders, ...);
		void DeletePrograms(const unsigned int* programs, ...);

		void ClearScreen(Color backgroundColor);
	}
}