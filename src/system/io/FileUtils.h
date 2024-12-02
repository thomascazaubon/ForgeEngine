#pragma once

#include <string>

namespace ForgeEngine
{
    namespace FileUtils
    {
        bool TryLoadFileContent(const std::string& filePath, std::string& fileContent);
    }
}
