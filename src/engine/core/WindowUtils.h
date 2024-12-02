#pragma once

#include <string>

struct GLFWwindow;

namespace ForgeEngine
{
	//Inits and return a GLFWWindow
	GLFWwindow* InitWindow(std::string name, unsigned int width, unsigned int height);
}