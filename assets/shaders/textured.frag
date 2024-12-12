#version 460 core

//FRAGMENT SHADER

uniform sampler2D RenderTexture;
uniform float LightIntensity = 1;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(RenderTexture, TexCoord) * vec4(LightIntensity, LightIntensity, LightIntensity, 1);
}