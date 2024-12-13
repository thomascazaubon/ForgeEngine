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

		std::vector<std::string> ExtractLines(const std::string& pattern, std::string source)
		{
			std::vector<std::string> extractedLines{};

			size_t lineStartIndex = 0;
			size_t endOfLineIndex = 0;
			std::string line;

			//For each found line
			while ((lineStartIndex = source.find(pattern)) != std::string::npos) {
				//Erase all characters prior to the found line
				source.erase(0, lineStartIndex);
				endOfLineIndex = source.find("\n");
				line = source.substr(0, endOfLineIndex);
				extractedLines.push_back(line);
				//Erase the found line
				source.erase(0, endOfLineIndex);
				//Proceed till no new line is found
			}

			return extractedLines;
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
