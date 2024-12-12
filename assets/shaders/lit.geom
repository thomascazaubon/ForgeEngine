#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout (location = 0) in vec2 aTextureCoordinatesIn;
layout (location = 1) in vec3 aNormalIn;
layout (location = 2) in vec4 aFragmentPositionIn;

layout (location = 0) out vec2 aTextureCoordinatesOut;
layout (location = 1) out vec3 aNormalOut;
layout (location = 2) out vec4 aFragmentPositionOut;


void main()
{
	aTextureCoordinatesOut = aTextureCoordinatesIn;
	aNormalOut = aNormalIn;
	aFragmentPositionOut = aFragmentPositionIn;

	for (int i = 0; i < gl_in.length(); i++) 
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}