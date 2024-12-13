#version 460 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;
uniform mat3 NormalMatrix;

//ATTRIBUTE 3
layout (location = 0) in vec3 inPosition;
//ATTRIBUTE 3
layout (location = 1) in vec3 inNormal;
//ATTRIBUTE 2
layout (location = 2) in vec2 inTextureCoordinates;

layout (location = 0) out vec2 outTextureCoordinates;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outFragmentPosition;

void main()
{
	gl_Position = Projection * View * Transform * vec4(inPosition, 1.0);

	outTextureCoordinates = inTextureCoordinates;
	outNormal = NormalMatrix * inNormal;
	outFragmentPosition = vec3(Transform * vec4(inPosition, 1.0));
}