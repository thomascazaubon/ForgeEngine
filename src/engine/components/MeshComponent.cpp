#include "MeshComponent.h"

#include "common/worldcomponents/SkyboxComponent.h"

#include "engine/assetloaders/ShaderLoader.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/render/Material.h"
#include "engine/render/Shader.h"
#include "engine/render/Texture.h"
#include "engine/worldcomponents/LightManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#endif //FORGE_DEBUG_ENABLED

#include <algorithm>
#include <iterator>
#include <utility>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    #define SET_SHADER_FLOAT(Identifier, Value) SetShaderFloat(Identifier, Value)
    #define SET_SHADER_BOOL(Identifier, Value) SetShaderBool(Identifier, Value)
    #define SET_SHADER_INT(Identifier, Value) SetShaderInt(Identifier, Value)
    #define SET_SHADER_COLOR(Identifier, Value) SetShaderColor(Identifier, Value)
    #define SET_SHADER_TEXTURE(Identifier, Value) SetShaderTexture(Identifier, Value)
    #define SET_SHADER_MATRIX3(Identifier, Value) SetShaderMatrix3(Identifier, Value)
    #define SET_SHADER_MATRIX4(Identifier, Value) SetShaderMatrix4(Identifier, Value)
    #define SET_SHADER_VECTOR3(Identifier, Value) SetShaderVector3(Identifier, Value)
    #define SET_SHADER_MATERIAL(Identifier, Value) SetShaderMaterial(Identifier, Value)
#else
    #define SET_SHADER_FLOAT(Identifier, Value) m_Shader->SetFloat(Identifier, Value)
    #define SET_SHADER_BOOL(Identifier, Value) m_Shader->SetBool(Identifier, Value)
    #define SET_SHADER_INT(Identifier, Value) m_Shader->SetInt(Identifier, Value)
    #define SET_SHADER_COLOR(Identifier, Value) m_Shader->SetColor(Identifier, Value)
    #define SET_SHADER_TEXTURE(Identifier, Value) m_Shader->SetTexture(Identifier, Value)
    #define SET_SHADER_MATRIX3(Identifier, Value) m_Shader->SetMatrix3(Identifier, Value)
    #define SET_SHADER_MATRIX4(Identifier, Value) m_Shader->SetMatrix4(Identifier, Value)
    #define SET_SHADER_VECTOR3(Identifier, Value) m_Shader->SetVector3(Identifier, Value)
    #define SET_SHADER_MATERIAL(Identifier, Value) m_Shader->SetMaterial(Identifier, Value)
#endif //FORGE_DEBUG_ENABLED

    MeshComponent::MeshComponent(const Mesh& mesh, const std::string& shaderPath, BillboardMode billboardMode /*= BillboardMode::Disabled*/)
        : Mother()
        , m_Mesh(mesh)
        , m_BillboardMode(billboardMode)
    {
        m_Shader = std::shared_ptr<Shader>(*(GameHandler::Get().GetWorld().GetComponentByType<ShaderLoader>()->GetOrLoadResource(shaderPath)));
        InitRender();
    }

    void MeshComponent::ResetRender()
    {
        glDeleteVertexArrays(1, &m_VertexArrayObject);
        m_VertexArrayObject = 0;
        glDeleteBuffers(1, &m_VertexBufferObject);
        m_VertexBufferObject = 0;
        glDeleteBuffers(1, &m_VertexBufferElement);
        m_VertexBufferElement = 0;
    }

    void MeshComponent::InitRender()
    {
        if (m_Shader == nullptr)
        {
#ifdef FORGE_DEBUG_ENABLED
            DebugUtils::LogError("MeshComponent::InitRender: Shader is missing.");
#endif //FORGE_DEBUG_ENABLED
            return;
        }

        std::vector<float> meshData = m_Mesh.MakeGLData(m_CurrentDrawMode);

        //Generates buffer to store vertices
        glGenVertexArrays(1, &m_VertexArrayObject);
        glGenBuffers(1, &m_VertexBufferObject);
        glGenBuffers(1, &m_VertexBufferElement);

        //Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

        //1. Bind Vertex Array Object
        glBindVertexArray(m_VertexArrayObject);

        //2. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
        const GLintptr meshDataSize = meshData.size() * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, meshDataSize, meshData.data(), GL_STATIC_DRAW);

        //2.5. Use vertex buffer element
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferElement);
        std::vector<unsigned int> indices = m_Mesh.GetTrianglesIndices();
        m_NumIndices = indices.size();
        const GLintptr indicesSize = indices.size() * sizeof(unsigned int);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

        //3. Then set our vertex attributes pointers
        //1st argument corresponds to the vertex attribute location (comes from vertexShaderSource)
        //2nd argument corresponds to the number of floats in the attribute (used in the vertex shader)
        //5th argument corresponds to the size of the attribute in bytes
        //Should be done for each attribute of the vertexShader, eg each in variable
        int offset = 0;
        const unsigned int inputDataSize = m_Shader->GetInputDataSize() * sizeof(float);
        for (unsigned int i = 0; i < m_Shader->GetNBAttributes() ; i++)
        {
            unsigned int attributeSize = m_Shader->GetAttributeSize(i);
            glVertexAttribPointer(i, attributeSize, GL_FLOAT, GL_FALSE, inputDataSize, (void*)offset);
            glEnableVertexAttribArray(i);
            offset += attributeSize * sizeof(float);
        }

        //Unbinding, this is optionnal

        //Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        //VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    void MeshComponent::OnUpdate(float dT)
    {
        if (false/*m_BillboardMode != BillboardMode::Disabled*/)
        {
            const CameraComponent& activeCamera = CameraComponent::GetActiveCamera();
            const Vector3 cameraPosition = activeCamera.GetOwner()->GetPosition();
            const Vector3 cameraPositionFinal = m_BillboardMode == BillboardMode::Full ? cameraPosition : Vector3(cameraPosition.x, GetOwner()->GetPosition().y, cameraPosition.z);
            const Vector3 direction = ForgeMaths::Normalize(cameraPositionFinal - GetOwner()->GetPosition());
            GetOwner()->GetTransform().LookAt(direction);
        }
    }

    void MeshComponent::OnPostUpdate(float dT)
    {
        Mother::OnPostUpdate(dT);

#ifdef FORGE_DEBUG_ENABLED
        if (m_ResetRequested)
        {
            ResetRender();
            InitRender();
            m_ResetRequested = false;
        }
#endif //FORGE_DEBUG_ENABLED

        if (m_Shader != nullptr)
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            m_Shader->Use();
            Matrix4 matrix = GetOwner()->GetTransform().GetMatrix();

            const CameraComponent& activeCamera = CameraComponent::GetActiveCamera();
            if (m_BillboardMode != BillboardMode::Disabled)
            {
                const Vector3 cameraPosition = activeCamera.GetOwner()->GetPosition();
                const Vector3 cameraPositionFinal = m_BillboardMode == BillboardMode::Full ? cameraPosition : Vector3(cameraPosition.x, GetOwner()->GetPosition().y, cameraPosition.z);
                const Vector3 direction = ForgeMaths::Normalize(cameraPositionFinal - GetOwner()->GetPosition());
                matrix = GetOwner()->GetTransform().MakeLookAt(direction);
            }

            SET_SHADER_MATRIX4(DEFAULT_TRANSFORM_NAME, matrix);
            //TODO: Don't do this per frame
            SET_SHADER_MATRIX3(DEFAULT_NORMAL_MATRIX_NAME, glm::mat3(glm::transpose(glm::inverse(m_Owner->GetTransform().GetMatrix()))));

            //Lighting
            std::vector<const LightComponent*> lights = GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->GetLightsInRange(GetOwner()->GetPosition());
            //TODO: support multiple lights
            if (!lights.empty())
            {
                SET_SHADER_BOOL(DEFAULT_HAS_POINT_LIGHTS_NAME, true);
                SET_SHADER_COLOR(DEFAULT_LIGHT_COLOR_NAME, lights[0]->GetColor());
                SET_SHADER_VECTOR3(DEFAULT_LIGHT_SOURCE_POSITION_NAME, lights[0]->GetOwner()->GetPosition());
                SET_SHADER_FLOAT(DEFAULT_LIGHT_INTENSITY_NAME, lights[0]->GetIntensity());
                SET_SHADER_FLOAT(DEFAULT_LIGHT_SOURCE_RANGE_NAME, lights[0]->GetRange());
            }
            else
            {
                SET_SHADER_BOOL(DEFAULT_HAS_POINT_LIGHTS_NAME, false);
            }

            float ambientLightIntensity = 1.f;

            if (const SkyboxComponent* skybox = GameHandler::Get().GetWorld().GetComponentByType<SkyboxComponent>())
            {
                ambientLightIntensity = skybox->GetAmbientLightIntensity();
            }

            SET_SHADER_FLOAT(DEFAULT_AMBIENT_LIGHT_INTENSITY_NAME, ambientLightIntensity);
            
            SET_SHADER_MATERIAL(DEFAULT_MATERIAL_NAME, *m_Mesh.GetMaterial());

            SET_SHADER_MATRIX4(DEFAULT_PROJECTION_NAME, activeCamera.GetProjection());
            SET_SHADER_MATRIX4(DEFAULT_VIEW_NAME, activeCamera.GetView());
            SET_SHADER_VECTOR3(DEFAULT_CAMERA_POSITION_NAME, activeCamera.GetOwner()->GetPosition());

            glBindVertexArray(m_VertexArrayObject);
            if (m_CurrentDrawMode == DrawMode::Elements)
            {
                glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLES, 0, 3 * m_Mesh.GetTrianglesCount() * m_Shader->GetInputDataSize());
            }
        }
    }

    void MeshComponent::OnDestroy() /*override*/
    {
        ResetRender();
        Mother::OnDestroy();
    }

#ifdef FORGE_DEBUG_ENABLED
    void MeshComponent::SetShaderFloat(const char* which, float value)
    {
        m_Shader->SetFloat(which, value);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("float", std::format("{:2}", value));
        }
    }

    void MeshComponent::SetShaderBool(const char* which, bool value)
    {
        m_Shader->SetBool(which, value);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("bool", std::format("{}", value ? "true" : false));
        }
    }

    void MeshComponent::SetShaderInt(const char* which, int value)
    {
        m_Shader->SetInt(which, value);

        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("int", std::format("{}", value));
        }
    }

    void MeshComponent::SetShaderColor(const char* which, const Color& value)
    {
        m_Shader->SetColor(which, value);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("vec4", value.ToString());
        }
    }

    void MeshComponent::SetShaderTexture(const char* which, const Texture* texture)
    {
        m_Shader->SetTexture(which, texture);
        if (m_RecordEnabled && m_Shader->HasUniform(which) && texture != nullptr)
        {
            m_RecordData.m_Data[which] = RecordData::Data("sampler2D", texture->GetDebugName());
        }
    }

    void MeshComponent::SetShaderMatrix4(const char* which, const glm::mat4& matrix)
    {
        m_Shader->SetMatrix4(which, matrix);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("mat4", DebugUtils::ToString(matrix));
        }
    }

    void MeshComponent::SetShaderMatrix3(const char* which, const glm::mat3& matrix)
    {
        m_Shader->SetMatrix3(which, matrix);
    }

    void MeshComponent::SetShaderVector3(const char* which, const Vector3& vector)
    {
        m_Shader->SetVector3(which, vector);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[which] = RecordData::Data("vec3", DebugUtils::ToString(vector));
        }
    }

    void MeshComponent::SetShaderMaterial(const char* which, const Material& material)
    {
        m_Shader->SetMaterial(which, material);
        if (m_RecordEnabled && m_Shader->HasUniform(which))
        {
            m_RecordData.m_Data[std::format("{}.{}", which, DEFAULT_MATERIAL_COLOR_NAME)] = RecordData::Data("vec4", material.GetColor().ToString());
            m_RecordData.m_Data[std::format("{}.{}", which, DEFAULT_MATERIAL_DIFFUSE_NAME)] = RecordData::Data("float", std::format("{}", material.GetDiffuse()));
            m_RecordData.m_Data[std::format("{}.{}", which, DEFAULT_MATERIAL_SPECULAR_NAME)] = RecordData::Data("float", std::format("{}", material.GetSpecular()));
            m_RecordData.m_Data[std::format("{}.{}", which, DEFAULT_MATERIAL_SHININESS_NAME)] = RecordData::Data("int", std::format("{}", material.GetShininess()));
            const Texture* texture = material.GetTexture();
            m_RecordData.m_Data[std::format("{}.{}", which, DEFAULT_MATERIAL_HAS_TEXTURE_NAME)] = RecordData::Data("bool", std::format("{}", texture != nullptr ? "true" : "false"));
            if (texture != nullptr)
            {
                m_RecordData.m_Data[DEFAULT_TEXTURE_NAME] = RecordData::Data("sampler2d", std::format("{}", material.GetTexture()->GetDebugName()));
            }
        }
    }

    void MeshComponent::OnDrawDebug(float dT) const
    {
        UpdateDrawModeCombo();
        ImGui::Text("VAO ID: %d", m_VertexArrayObject);
        ImGui::Text("VBO ID: %d", m_VertexBufferObject);
        ImGui::Text("VBE ID: %d", m_VertexBufferElement);
        ImGui::Text("Num Indices: %d", m_NumIndices);
        m_Mesh.OnDrawDebug(m_CurrentDrawMode);
        if (ImGui::CollapsingHeader("Shader Records"))
        {
            m_RecordEnabled = true;
            DebugShaderRecords();
        }
        else
        {
            m_RecordEnabled = false;
        }
    }

    void MeshComponent::UpdateDrawModeCombo() const
    {
        ImGuiUtils::PushId((int)this);
        if (ImGui::BeginCombo("Current Draw Mode", m_CurrentDrawMode == DrawMode::Arrays ? "Arrays" : "Elements"))
        {
            for (int i = 0; i < 2; i++)
            {
                const DrawMode drawMode = static_cast<DrawMode>(i);
                const bool isSelected = drawMode == m_CurrentDrawMode;

                if (ImGui::Selectable(drawMode == DrawMode::Arrays ? "Arrays" : "Elements", isSelected))
                {
                    m_CurrentDrawMode = drawMode;
                    m_ResetRequested = true;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::PopID();
    }

    void MeshComponent::DebugShaderRecords() const
    {
        if (ImGui::BeginTable("Records", 3, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders))
        {
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Value");
            ImGui::TableHeadersRow();
            for (const auto& pair : m_RecordData.m_Data)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextColored(ImGuiUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.first.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::TextColored(ImGuiUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.second.m_Type.c_str());
                ImGui::TableSetColumnIndex(2);
                ImGui::TextColored(ImGuiUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.second.m_Value.c_str());
            }
            ImGui::EndTable();
        }

        m_RecordData.m_Data.clear();
    }
#endif //FORGE_DEBUG_ENABLED
}