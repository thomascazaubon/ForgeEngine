#version 330 core

//FRAGMENT SHADER

uniform float AmbientLightIntensity;
uniform vec4 RenderColor;
uniform vec4 LightColor;
uniform vec4 LightSourcePosition;
uniform vec4 CameraPosition;
uniform float LightRange;
uniform sampler2D RenderTexture;
uniform int Shininess;
uniform float SpecularIntensity;
uniform bool UseTexture;

struct MaterialData {
    vec4 color;
    float diffuse;
    float specular;
    int shininess;
}; 
  
uniform MaterialData Material;

in vec3 ourNormal;
in vec4 ourFragmentPosition;
in vec2 ourTextureCoordinates;

out vec4 FragColor;

void main()
{
    vec3 directionToLight = vec3(LightSourcePosition - ourFragmentPosition);
	float distanceToLight = length(directionToLight);
	float distanceRatio = distanceToLight / LightRange;
	vec3 directionToLightNormalized = normalize(directionToLight);
	vec3 eyeDirection = vec3(normalize(CameraPosition - ourFragmentPosition));
	vec3 lightRayReflection = reflect(-directionToLightNormalized, ourNormal);
	
	float specularFactor = pow(max(dot(eyeDirection, lightRayReflection), 0), Material.shininess);
	vec4 specularLight = LightColor * (Material.specular * Material.color * specularFactor)  * (1 - distanceRatio);

	float diffuseFactor = max(dot(directionToLightNormalized, ourNormal), 0.0);
	vec4 diffuseLight = diffuseFactor * Material.color * Material.diffuse * LightColor * (1 - distanceRatio);

	vec4 result;

	if (UseTexture)
	{
		result = texture(RenderTexture, ourTextureCoordinates) * Material.color * (diffuseLight + specularLight + AmbientLightIntensity);
	}
	else
	{
		result = Material.color * (diffuseLight + specularLight + AmbientLightIntensity);
	}

	FragColor = vec4(result.x, result.y, result.z, Material.color.w);
}