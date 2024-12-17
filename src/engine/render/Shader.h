#pragma once

#include "engine/assetloaders/LoadableAsset.h"
#include "engine/math/Matrix4.h"

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ForgeEngine
{
	#define GLSL_ATTRIBUTE_TOKEN			        "//ATTRIBUTE"
	#define GLSL_UNIFORM_TOKEN			            "uniform"

	#define DEFAULT_VERTEX_SHADER_PATH		        "assets\\shaders\\vertex\\default.vert"
	#define DEFAULT_FRAGMENT_SHADER_PATH	        "assets\\shaders\\fragment\\default.frag"

	#define TEXTURED_VERTEX_SHADER_PATH		        "assets\\shaders\\vertex\\textured.vert"
	#define TEXTURED_FRAGMENT_SHADER_PATH	        "assets\\shaders\\fragment\\textured.frag"

    #define LIT_VERTEX_SHADER_PATH		            "assets\\shaders\\vertex\\lit.vert"
    #define LIT_GEOMETRY_SHADER_PATH		        "assets\\shaders\\vertex\\lit.geom"
    #define LIT_FRAGMENT_SHADER_PATH	            "assets\\shaders\\fragment\\lit.frag"

    #define DEBUG_VERTEX_SHADER_PATH		        "assets\\shaders\\vertex\\debug.vert"
    #define DEBUG_FRAGMENT_SHADER_PATH	            "assets\\shaders\\fragment\\debug.frag"

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
    #define DEFAULT_HAS_POINT_LIGHTS_NAME	        "HasPointLights"

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
	class MeshComponent;
	class Texture;

	class Shader : public LoadableAsset
	{
        public:
#ifdef FORGE_DEBUG_ENABLED
            struct RecordData
            {
                struct Data
                {
                    Data() : m_Type(""), m_Value("") {}
                    Data(const std::string& type, const std::string& value) : m_Type(type), m_Value(value) {}

                    std::string m_Type;
                    std::string m_Value;
                };

                std::map<std::string, Data> m_Data;
            };
#endif //FORGE_DEBUG_ENABLED

            Shader(const std::string& shaderPath);
            ~Shader();

            //TODO: fix this
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "TODO"; }
            void OnDrawDebug() const override;
            void ClearRecordedData() { m_RecordedData.clear(); }

            const RecordData* GetRecordData(const MeshComponent* dataOwner) const;
#endif //FORGE_DEBUG_ENABLED

            void Use() const;

            bool IsValid() const override { return m_ProgramID && m_VertexID&& m_FragmentID; }

            int GetInputDataSize() const;

            size_t GetNBAttributes() const { return m_AttributesSizes.size(); }
            unsigned int GetAttributeSize(int index) const;
            const auto& GetAttributesSizes() const { return m_AttributesSizes; }

            //Use should be called before calling any of the following!
            void SetFloat(const char* which, float value, const MeshComponent* callerAdress = nullptr);
            void SetBool(const char* which, bool value, const MeshComponent* callerAdress = nullptr);
            void SetInt(const char* which, int value, const MeshComponent* callerAdress = nullptr);
            void SetColor(const char* which, const Color& value, const MeshComponent* callerAdress = nullptr);
            void SetTexture(unsigned int which, const Texture* texture, const MeshComponent* callerAdress = nullptr);
            void SetMatrix4(const char* which, const glm::mat4& matrix, const MeshComponent* callerAdress = nullptr);
            void SetMatrix3(const char* which, const glm::mat3& matrix, const MeshComponent* callerAdress = nullptr);
            void SetVector3(const char* which, const Vector3& vector, const MeshComponent* callerAdress = nullptr);
            void SetMaterial(const Material& material, const MeshComponent* callerAdress = nullptr);

		private:
#ifdef FORGE_DEBUG_ENABLED
            struct UniformData
            {
                std::string m_VariableName;
                std::string m_VariableType;
            };

            void ParseUniforms(const std::string& fileContent);
            void OrderUniforms();

            const UniformData* GetUniformData(const std::string& uniformName) const;

			std::vector<UniformData> m_UniformsData{};
            std::unordered_map<const MeshComponent*, RecordData> m_RecordedData;
#endif //FORGE_DEBUG_ENABLED
           
			//Stores the attributes declared in the shader source using the GLSL_ATTRIBUTE_TOKEN (must be declared in the right order !
			std::vector<unsigned int> m_AttributesSizes{};

            unsigned int m_ProgramID{0};
            unsigned int m_VertexID{0};
            unsigned int m_GeometryID{0};
            unsigned int m_FragmentID{0};
			mutable int m_InputDataSize{-1};
	};
}