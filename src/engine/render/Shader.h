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
    #define GLSL_ATTRIBUTE_TOKEN                      "//ATTRIBUTE"
    #define GLSL_UNIFORM_TOKEN                        "uniform"
    #define GLSL_TEXTURE_TOKEN                        "sampler"

    #define DEFAULT_VERTEX_SHADER_PATH                "assets\\shaders\\vertex\\default.vert"
    #define DEFAULT_FRAGMENT_SHADER_PATH              "assets\\shaders\\fragment\\default.frag"

    #define TEXTURED_VERTEX_SHADER_PATH               "assets\\shaders\\vertex\\textured.vert"
    #define TEXTURED_FRAGMENT_SHADER_PATH             "assets\\shaders\\fragment\\textured.frag"

    #define LIT_VERTEX_SHADER_PATH                    "assets\\shaders\\vertex\\lit.vert"
    #define LIT_GEOMETRY_SHADER_PATH                  "assets\\shaders\\vertex\\lit.geom"
    #define LIT_FRAGMENT_SHADER_PATH                  "assets\\shaders\\fragment\\lit.frag"

    #define DEBUG_VERTEX_SHADER_PATH                  "assets\\shaders\\vertex\\debug.vert"
    #define DEBUG_FRAGMENT_SHADER_PATH                "assets\\shaders\\fragment\\debug.frag"

    #define DEFAULT_RENDER_COLOR_NAME                 "RenderColor"

    #define DEFAULT_AMBIENT_LIGHT_INTENSITY_NAME      "AmbientLightIntensity"
    #define DEFAULT_LIGHT_INTENSITY_NAME              "LightIntensity"
    #define DEFAULT_LIGHT_COLOR_NAME                  "LightColor"
    #define DEFAULT_LIGHT_SOURCE_POSITION_NAME        "LightSourcePosition"
    #define DEFAULT_LIGHT_SOURCE_RANGE_NAME           "LightRange"
    #define DEFAULT_SHININESS_NAME                    "Shininess"
    #define DEFAULT_SPECULAR_INTENSITY_NAME           "SpecularIntensity"
    #define DEFAULT_HAS_POINT_LIGHTS_NAME             "HasPointLights"

    #define DEFAULT_TRANSFORM_NAME                    "Transform"
    #define DEFAULT_PROJECTION_NAME                   "Projection"
    #define DEFAULT_VIEW_NAME                         "View"
    #define DEFAULT_NORMAL_MATRIX_NAME                "NormalMatrix"
    #define DEFAULT_CAMERA_POSITION_NAME              "CameraPosition"
    #define DEFAULT_TEXTURE_NAME                      "Texture"

    #define DEFAULT_MATERIAL_NAME                     "Material"
    #define DEFAULT_MATERIAL_COLOR_NAME               "color"
    #define DEFAULT_MATERIAL_DIFFUSE_NAME             "diffuse"
    #define DEFAULT_MATERIAL_SPECULAR_NAME            "specular"
    #define DEFAULT_MATERIAL_SHININESS_NAME           "shininess"
    #define DEFAULT_MATERIAL_HAS_TEXTURE_NAME         "hasTexture"
    

    class Color;
    class Material;
    class Texture;

    class Shader : public LoadableAsset
    {
        using Mother = LoadableAsset;

        template<typename T>
        friend class AssetLoader;

        public:
            ~Shader();

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const override;

            bool HasUniform(const std::string& name) const { return GetUniformData(name) != nullptr; }
#endif //FORGE_DEBUG_ENABLED

            void Use() const;

            bool IsValid() const override { return m_ProgramID && m_VertexID && m_FragmentID; }

            int GetInputDataSize() const;

            size_t GetNBAttributes() const { return m_AttributesSizes.size(); }
            unsigned int GetAttributeSize(int index) const;
            const auto& GetAttributesSizes() const { return m_AttributesSizes; }

            //Use should be called before calling any of the following!
            void SetFloat(const char* which, float value);
            void SetBool(const char* which, bool value);
            void SetInt(const char* which, int value);
            void SetColor(const char* which, const Color& value);
            void SetTexture(const char* which, const Texture* texture);
            void SetMatrix4(const char* which, const glm::mat4& matrix);
            void SetMatrix3(const char* which, const glm::mat3& matrix);
            void SetVector3(const char* which, const Vector3& vector);
            void SetMaterial(const char* which, const Material& material);

        private:
            Shader(const std::string& path);

#ifdef FORGE_DEBUG_ENABLED
            struct UniformData
            {
                std::string m_VariableName;
                std::string m_VariableType;

                bool IsComplexType() const { return !m_SubData.empty(); }

                std::vector<UniformData> m_SubData{};
            };

            void ParseUniforms(const std::string& fileContent);
            void OrderUniforms();

            const UniformData* GetUniformData(const std::string& uniformName) const;

            std::vector<UniformData> m_UniformsData{};
#endif //FORGE_DEBUG_ENABLED
           
           int GetTextureUnit(const std::string& which) const;
           void ParseTextures(const std::string& fileContent);

            //Stores the attributes declared in the shader source using the GLSL_ATTRIBUTE_TOKEN (must be declared in the right order !
            std::vector<unsigned int> m_AttributesSizes{};
            std::vector<std::string> m_TextureUnits{};

            unsigned int m_ProgramID{0};
            unsigned int m_VertexID{0};
            unsigned int m_GeometryID{0};
            unsigned int m_FragmentID{0};
            mutable int m_InputDataSize{-1};
    };
}