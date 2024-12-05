#version 330 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = Projection * View * Transform * vec4(aPos, 1.0);
}