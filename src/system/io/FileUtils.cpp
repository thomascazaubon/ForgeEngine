#include "FileUtils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ForgeEngine
{
    namespace FileUtils
    {
        bool TryLoadFileContent(const std::string& filePath, std::string& fileContent)
        {
            //TODO: make this a util function
            std::ifstream sourceFile;
            std::stringstream sourceStream;
            std::string sourceContent{};

            // ensure ifstream objects can throw exceptions:
            sourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                sourceFile.open(filePath);
                sourceStream << sourceFile.rdbuf();
                sourceFile.close();

                fileContent = sourceStream.str();

                return true;
            }
            catch (std::ifstream::failure failure)
            {
                std::cout << "FileUtils: Cannot open source path " << filePath << "." << std::endl;

                return false;
            }
        }
    }
}
