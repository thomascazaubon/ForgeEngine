#version 330 core

//FRAGMENT SHADER

struct MaterialData {
    vec4 color;
    float diffuse;
    float specular;
    int shininess;
}; 
  
uniform MaterialData Material;

out vec4 FragColor;

void main()
{
	FragColor = Material.color;
}