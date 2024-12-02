#pragma once

#include <string>
#include <vector>

namespace ForgeEngine
{
	namespace ForgeUtils
	{
		//Extract all lines beginning by the given pattern from the given source
		std::vector<std::string> ExtractLines(const std::string& pattern, std::string source);
		//Split a given string using the given pattern
		std::vector<std::string> Split(const std::string& pattern, std::string source);
	}
}