#version 460 core

//FRAGMENT SHADER

uniform vec4 RenderColor;

out vec4 FragColor;

void main()
{
	FragColor = RenderColor;
}