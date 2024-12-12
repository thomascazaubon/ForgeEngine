#version 460 core

//VERTEX SHADER

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;
uniform mat3 NormalMatrix;

//ATTRIBUTE 3
layout (location = 0) in vec3 aPositionIn;
//ATTRIBUTE 3
layout (location = 1) in vec3 aNormalIn;
//ATTRIBUTE 2
layout (location = 2) in vec2 aTextureCoordinatesIn;

layout (location = 0) out vec2 aTextureCoordinatesOut;
layout (location = 1) out vec3 aNormalOut;
layout (location = 2) out vec4 aFragmentPositionOut;

void main()
{
	gl_Position = Projection * View * Transform * vec4(aPositionIn, 1.0);

	aTextureCoordinatesOut = aTextureCoordinatesIn;
	aNormalOut = NormalMatrix * aNormalIn;
	aFragmentPositionOut = Transform * vec4(aPositionIn, 1.0);
}