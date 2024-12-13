#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec4 CameraPosition;

layout (location = 0) in vec2 inTextureCoordinates[];
layout (location = 1) in vec3 inNormal[];
layout (location = 2) in vec4 inFragmentPosition[];

layout (location = 0) out vec2 outTextureCoordinates;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec4 outFragmentPosition;

void main()
{
	for (int i = 0; i < gl_in.length(); i++) 
	{
		gl_Position = gl_in[i].gl_Position;
		outTextureCoordinates = inTextureCoordinates[i];
		outNormal = inNormal[i];
		outFragmentPosition = inFragmentPosition[i];
		EmitVertex();
	}

	EndPrimitive();
}