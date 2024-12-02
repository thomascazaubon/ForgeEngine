#version 330 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;
uniform mat3 NormalMatrix;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPosition;
//ATTRIBUTE 3
layout (location = 1) in vec3 aNormal;
//ATTRIBUTE 2
layout (location = 2) in vec2 aTextureCoordinates;

out vec2 ourTextureCoordinates;
out vec3 ourNormal;
out vec4 ourFragmentPosition;

void main()
{
	gl_Position = Projection * View * Transform * vec4(aPosition, 1.0);
	ourNormal = NormalMatrix * aNormal; ;
	ourFragmentPosition = Transform * vec4(aPosition, 1.0);
	ourTextureCoordinates = aTextureCoordinates;
}