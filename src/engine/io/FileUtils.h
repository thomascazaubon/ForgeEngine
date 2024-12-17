#pragma once

#include <string>
#include <vector>

namespace ForgeEngine
{
    namespace FileUtils
    {
        bool TryLoadFileContent(const std::string& filePath, std::string& fileContent, bool verbose = false);

        //Extract all lines beginning by the given pattern from the given source, maxLines = 0 means unlimited search
        std::vector<std::string> ExtractLines(const std::string& pattern, const std::string& source, unsigned int maxLines = 0);
        //Extract string from source starting at pattern index excluded to endPattern excluded
        std::string ExtractString(const std::string& pattern, const std::string& endPattern, std::string source);

        //Split a given string using the given pattern
        std::vector<std::string> Split(const std::string& pattern, std::string source);
    }
}
