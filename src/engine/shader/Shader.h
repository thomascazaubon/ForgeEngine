#pragma once

#include "engine/core/LoadableResource.h"
#include "system/math/Matrix4.h"

#include <utility>
#include <vector>
#include <string>

namespace ForgeEngine
{
	#define GLSL_ATTRIBUTE_TOKEN			"//ATTRIBUTE"

	#define DEFAULT_VERTEX_SHADER_PATH		"assets\\shaders\\vertex\\default.glslv"
	#define DEFAULT_FRAGMENT_SHADER_PATH	"assets\\shaders\\fragment\\default.glslf"

	#define TEXTURED_VERTEX_SHADER_PATH		"assets\\shaders\\vertex\\textured.glslv"
	#define TEXTURED_FRAGMENT_SHADER_PATH	"assets\\shaders\\fragment\\textured.glslf"

    #define LIT_VERTEX_SHADER_PATH		    "assets\\shaders\\vertex\\lit.glslv"
    #define LIT_FRAGMENT_SHADER_PATH	    "assets\\shaders\\fragment\\lit.glslf"

	#define DEFAULT_RENDER_COLOR_NAME		        "RenderColor"
	#define DEFAULT_RENDER_TEXTURE_NAME		        "RenderTexture"
	#define DEFAULT_USE_TEXTURE_NAME		        "UseTexture"

	#define DEFAULT_AMBIENT_LIGHT_INTENSITY_NAME    "AmbientLightIntensity"
	#define DEFAULT_LIGHT_INTENSITY_NAME	        "LightIntensity"
    #define DEFAULT_LIGHT_COLOR_NAME		        "LightColor"
    #define DEFAULT_LIGHT_SOURCE_POSITION_NAME	    "LightSourcePosition"
    #define DEFAULT_LIGHT_SOURCE_RANGE_NAME	        "LightRange"
    #define DEFAULT_SHININESS_NAME	                "Shininess"
    #define DEFAULT_SPECULAR_INTENSITY_NAME	        "SpecularIntensity"

	#define DEFAULT_TRANSFORM_NAME			        "Transform"
	#define DEFAULT_PROJECTION_NAME			        "Projection"
	#define DEFAULT_VIEW_NAME				        "View"
	#define DEFAULT_NORMAL_MATRIX_NAME				"NormalMatrix"
	#define DEFAULT_CAMERA_POSITION_NAME			"CameraPosition"

    #define DEFAULT_MATERIAL_COLOR_NAME	            "Material.color"
    #define DEFAULT_MATERIAL_DIFFUSE_NAME	        "Material.diffuse"
    #define DEFAULT_MATERIAL_SPECULAR_NAME	        "Material.specular"
    #define DEFAULT_MATERIAL_SHININESS_NAME	        "Material.shininess"
	

	class Color;
	class Material;
	class Texture;

	class Shader : public LoadableResource
	{
        public:
            Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
            ~Shader();

            //TODO: fix this
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "TODO"; }
            void OnDrawDebug() const override;
#endif //FORGE_DEBUG_ENABLED

            void Use();

            bool IsValid() const override { return m_ProgramID && m_VertexID&& m_FragmentID; }

            int GetInputDataSize() const;

            size_t GetNBAttributes() const { return m_AttributesSizes.size(); }
            unsigned int GetAttributeSize(int index) const;
            const auto& GetAttributesSizes() const { return m_AttributesSizes; }

            //Use should be called before calling any of the following!
            void SetFloat(const char* which, float value);
            void SetBool(const char* which, bool value);
            void SetInt(const char* which, int value);
            void SetColor(const char* which, const Color& value);
            void SetTexture(unsigned int which, const Texture* texture);
            void SetMatrix4(const char* which, const glm::mat4& matrix);
            void SetMatrix3(const char* which, const glm::mat3& matrix);
            void SetVector4(const char* which, const Vector3& vector);
            void SetMaterial(const Material& material);

		private:
            unsigned int m_ProgramID{};
            unsigned int m_VertexID{};
            unsigned int m_FragmentID{};

			//Stores the attributes declared in the shader source using the GLSL_ATTRIBUTE_TOKEN (must be declared in the right order !
			std::vector<unsigned int> m_AttributesSizes{};

			mutable int m_InputDataSize{-1};
	};
}