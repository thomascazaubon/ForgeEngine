#include "Utils.h"

namespace ForgeEngine
{
	namespace ForgeUtils
	{
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