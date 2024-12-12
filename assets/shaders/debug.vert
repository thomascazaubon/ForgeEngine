#version 460 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = Projection * View * vec4(aPos, 1.0);
}