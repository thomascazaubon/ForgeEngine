#include "FileUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#endif //FORGE_DEBUG_ENABLED

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ForgeEngine
{
    namespace FileUtils
    {
        bool TryLoadFileContent(const std::string& filePath, std::string& fileContent, bool verbose /*= false*/)
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
                if (verbose)
                {
#ifdef FORGE_DEBUG_ENABLED
                    DebugUtils::LogWarning("FileUtils: Cannot open source path {}", filePath.c_str());
#endif //FORGE_DEBUG_ENABLED
                }

                return false;
            }
        }

        std::vector<std::string> ExtractLines(const std::string& pattern, const std::string& source, unsigned int maxLines /*= 0*/)
        {
            std::vector<std::string> extractedLines{};
            std::string sourceCopy = source;

            size_t lineStartIndex = 0;
            size_t endOfLineIndex = 0;
            std::string line;

            unsigned int foundLines = 0;

            //For each found line
            while ((lineStartIndex = sourceCopy.find(pattern)) != std::string::npos) {
                //Erase all characters prior to the found line
                sourceCopy.erase(0, lineStartIndex);
                endOfLineIndex = sourceCopy.find("\n");
                line = sourceCopy.substr(0, endOfLineIndex);
                extractedLines.push_back(line);
                //Erase the found line
                sourceCopy.erase(0, endOfLineIndex);
                //Proceed till no new line is found
                if (++foundLines == maxLines && maxLines > 0)
                {
                    break;
                }
            }

            return extractedLines;
        }

        std::string ExtractString(const std::string& pattern, const std::string& endPattern, std::string source)
        {
            std::string extractedString;
            std::string sourceCopy = source;
            size_t startIndex = sourceCopy.find(pattern);

            if (startIndex != std::string::npos)
            {
                sourceCopy.erase(0, startIndex + pattern.size());
                size_t endIndex = sourceCopy.find(endPattern);
                if (endIndex != std::string::npos)
                {
                    sourceCopy.erase(endIndex, sourceCopy.size() - endIndex);
                }
                extractedString = sourceCopy;
            }

            return extractedString;
        }

        std::vector<std::string> Split(const std::string& pattern, std::string source)
        {
            std::vector<std::string> splittedString{};

            size_t patternIndex = 0;
            std::string token;

            while ((patternIndex = source.find(pattern)) != std::string::npos) {
                token = source.substr(0, patternIndex);
                splittedString.push_back(token);
                source.erase(0, patternIndex + pattern.length());
            }
            splittedString.push_back(source);

            return splittedString;
        }
    }
}
