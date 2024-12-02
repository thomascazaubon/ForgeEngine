#include "ShaderUtils.h"

#include "engine/core/OpenGL.h"
#include "system/misc/Color.h"

#include <iostream>
#include <stdarg.h>

namespace ForgeEngine
{
	namespace ShaderUtils
	{
		#define LOG_SIZE 512

		bool TryCompileShader(unsigned int& shader, const char* shaderPath, const char* shaderSource, int shaderType, bool outputLogs /* = true*/)
		{
			//Compile shader
			shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			//Check if compilation was successful
			int compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationSuccess);

			//Output log if needed
			if (!compilationSuccess && outputLogs)
			{
                //TODO: Add detailed logs
				glGetShaderInfoLog(shader, LOG_SIZE, nullptr, infoLog);
				std::cout << shaderPath << "\n" << infoLog << std::endl;
                exit(-1);
			}

			return static_cast<bool>(compilationSuccess);
		}

		bool TryLinkShaderProgram(unsigned int& shaderProgram, bool outputLogs, const unsigned int* shaders, ...)
		{
			va_list args;

			//Creates shader program
			shaderProgram = glCreateProgram();

			//Links all shaders into the shaderProgram
			va_start(args, shaders);

			while (*shaders) {
				glAttachShader(shaderProgram, *shaders);
				++shaders;
			}

			va_end(args);

			glLinkProgram(shaderProgram);

			//Check if linking was successful
			int compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationSuccess);

			//Output log if needed
			if (!compilationSuccess && outputLogs)
			{
				glGetShaderInfoLog(shaderProgram, LOG_SIZE, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			return static_cast<bool>(compilationSuccess);
		}

		void DeleteShaders(const unsigned int* shaders, ...)
		{
			va_list args;
			va_start(args, shaders);

			while (*shaders) {
				glDeleteShader(*shaders);
				++shaders;
			}

			va_end(args);
		}

		void DeletePrograms(const unsigned int* programs, ...)
		{
			va_list args;
			va_start(args, programs);

			while (*programs) {
				glDeleteProgram(*programs);
				++programs;
			}

			va_end(args);
		}

		void ClearScreen(Color backgroundColor)
		{
			// set state color
			glClearColor(backgroundColor.GetRRatio(), backgroundColor.GetGRatio(), backgroundColor.GetBRatio(), backgroundColor.GetA());
			// applies state
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}