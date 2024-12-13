#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec3 CameraPosition;

layout (location = 0) in vec2 inTextureCoordinates[];
layout (location = 1) in vec3 inNormal[];
layout (location = 2) in vec3 inFragmentPosition[];

layout (location = 0) out vec2 outTextureCoordinates;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outFragmentPosition;

void main()
{
	for (int i = 0; i < gl_in.length(); i++) 
	{
		vec3 position =  gl_in[i].gl_Position.xyz;
		vec3 directionToCamera = normalize(CameraPosition - position);
		vec3 sideVector = cross(directionToCamera, vec3(0.0,1.0,0.0));

		gl_Position = gl_in[i].gl_Position;
		outTextureCoordinates = inTextureCoordinates[i];
		outNormal = inNormal[i];
		outFragmentPosition = inFragmentPosition[i];
		EmitVertex();
	}

	EndPrimitive();
}