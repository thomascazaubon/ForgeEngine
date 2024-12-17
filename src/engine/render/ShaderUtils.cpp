#include "ShaderUtils.h"

#include "engine/render/Color.h"

namespace ForgeEngine
{
    namespace ShaderUtils
    {
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
            }

            return static_cast<bool>(compilationSuccess);
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