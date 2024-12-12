#version 460 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPos;
//ATTRIBUTE 3
layout (location = 1) in vec3 aNormal;
//ATTRIBUTE 2
layout (location = 2) in vec2 aTextureCoordinates;

out vec4 ourColor;

void main()
{
	gl_Position = Projection * View * Transform * vec4(aPos, 1.0);
}