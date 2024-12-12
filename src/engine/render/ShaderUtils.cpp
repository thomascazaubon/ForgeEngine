#include "ShaderUtils.h"

#include "engine/render/Color.h"
#include "engine/render/OpenGL.h"

#include <iostream>
#include <stdarg.h>

namespace ForgeEngine
{
	namespace ShaderUtils
	{
		#define LOG_SIZE 1024

		bool TryCompileShader(unsigned int& shader, const char* shaderSource, int shaderType, std::string& logs)
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
			if (!compilationSuccess)
			{
                //TODO: Add detailed logs
				glGetShaderInfoLog(shader, LOG_SIZE, nullptr, infoLog);
				logs = infoLog;
                exit(-1);
			}

			return static_cast<bool>(compilationSuccess);
		}

		bool TryLinkShaderProgram(unsigned int& shaderProgram, std::string& logs, const unsigned int* shaders, ...)
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

			//Check if linkage was successful
			int compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationSuccess);

			if (!compilationSuccess)
			{
				glGetShaderInfoLog(shaderProgram, LOG_SIZE, nullptr, infoLog);
				logs = infoLog;
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