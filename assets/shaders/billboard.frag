#version 460 core

//FRAGMENT SHADER

uniform float AmbientLightIntensity;
uniform vec4 LightColor;
uniform vec3 LightSourcePosition;
uniform vec3 CameraPosition;
uniform float LightRange;
uniform bool HasPointLights;
uniform sampler2D Texture;

struct MaterialData {
    vec4 color;
    float diffuse;
    float specular;
    int shininess;
    bool hasTexture;
};
  
uniform MaterialData Material;

layout (location = 0) in vec2 inTextureCoordinates;
layout (location = 1) in vec3 inFragmentPosition;

out vec4 FragColor;

void main()
{
    vec3 normal = CameraPosition - inFragmentPosition;
    normal.y = 0.0;
    normal = normalize(normal);

    vec3 directionToLight = LightSourcePosition - inFragmentPosition;
	float distanceToLight = length(directionToLight);
	float distanceRatio = distanceToLight / LightRange;
	vec3 directionToLightNormalized = normalize(directionToLight);
	vec3 eyeDirection = normalize(CameraPosition - inFragmentPosition);
	vec3 lightRayReflection = reflect(-directionToLightNormalized, normal);
	
	float specularFactor = pow(max(dot(eyeDirection, lightRayReflection), 0), Material.shininess);
	vec4 specularLight = LightColor * (Material.specular * Material.color * specularFactor)  * (1 - distanceRatio);

    
	float diffuseFactor = max(dot(directionToLightNormalized, normal), 0.0);
	vec4 diffuseLight = diffuseFactor * Material.color * Material.diffuse * LightColor * (1 - distanceRatio);

	vec4 result;

	if (Material.hasTexture)
	{
		vec4 texture = texture(Texture, inTextureCoordinates).rgba;

		if (HasPointLights)
		{
			result = texture * Material.color * (diffuseLight + specularLight + AmbientLightIntensity);
		}
		else
		{
		result = texture * Material.color * AmbientLightIntensity;
		}
		
		result.w = texture.w * Material.color.w;
	}
	else
	{
		result = Material.color * (diffuseLight + specularLight + AmbientLightIntensity);
	}

	FragColor = vec4(result.x, result.y, result.z, result.w);
}