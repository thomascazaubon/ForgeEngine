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
	MeshComponent::MeshComponent(const Mesh& mesh, const std::string& shaderPath, BillboardMode billboardMode /*= BillboardMode::Disabled*/)
        : Mother()
        , m_Mesh(mesh)
        , m_BillboardMode(billboardMode)
	{
        m_Shader = std::shared_ptr<Shader>(*(GameHandler::Get().GetWorld().GetComponentByType<ShaderLoader>()->GetOrLoadResource(shaderPath)));
		InitRender();
	}

	void MeshComponent::InitRender()
	{
        if (m_Shader == nullptr)
        {
            //TODO: Add error message
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
		Mother::OnUpdate(dT);

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

			m_Shader->SetMatrix4(DEFAULT_TRANSFORM_NAME, matrix
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);
            //TODO: Don't do this per frame
			m_Shader->SetMatrix3(DEFAULT_NORMAL_MATRIX_NAME, glm::mat3(glm::transpose(glm::inverse(m_Owner->GetTransform().GetMatrix())))
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);

            //Lighting
            std::vector<const LightComponent*> lights = GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->GetLightsInRange(GetOwner()->GetPosition());
			//TODO: support multiple lights
            if (!lights.empty())
            {
				m_Shader->SetBool(DEFAULT_HAS_POINT_LIGHTS_NAME, true
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
					);
                m_Shader->SetColor(DEFAULT_LIGHT_COLOR_NAME, lights[0]->GetColor()
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
				);
                m_Shader->SetVector3(DEFAULT_LIGHT_SOURCE_POSITION_NAME, lights[0]->GetOwner()->GetPosition()
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
				);
                m_Shader->SetFloat(DEFAULT_LIGHT_INTENSITY_NAME, lights[0]->GetIntensity()
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
				);
                m_Shader->SetFloat(DEFAULT_LIGHT_SOURCE_RANGE_NAME, lights[0]->GetRange()
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
				);
            }
			else
			{
				m_Shader->SetBool(DEFAULT_HAS_POINT_LIGHTS_NAME, false
#ifdef FORGE_DEBUG_ENABLED
					, m_RecordEnabled ? this : nullptr
#endif
				);
			}

			float ambientLightIntensity = 1.f;

			if (const SkyboxComponent* skybox = GameHandler::Get().GetWorld().GetComponentByType<SkyboxComponent>())
			{
				ambientLightIntensity = skybox->GetAmbientLightIntensity();
			}

            m_Shader->SetFloat(DEFAULT_AMBIENT_LIGHT_INTENSITY_NAME, ambientLightIntensity
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);
			
            m_Shader->SetMaterial(*m_Mesh.GetMaterial()
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);

			m_Shader->SetMatrix4(DEFAULT_PROJECTION_NAME, activeCamera.GetProjection()
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);
			m_Shader->SetMatrix4(DEFAULT_VIEW_NAME, activeCamera.GetView()
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);
			m_Shader->SetVector3(DEFAULT_CAMERA_POSITION_NAME, activeCamera.GetOwner()->GetPosition()
#ifdef FORGE_DEBUG_ENABLED
				, m_RecordEnabled ? this : nullptr
#endif
			);

			glBindVertexArray(m_VertexArrayObject);
			if (m_CurrentDrawMode == DrawMode::Elements)
			{
				//TODO: Fix this
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
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_VertexBufferElement);
		Mother::OnDestroy();
	}

#ifdef FORGE_DEBUG_ENABLED
    void MeshComponent::OnDrawDebug(float dT) const
    {
		UpdateDrawModeCombo();
        ImGui::Text("VAO ID: %d", m_VertexArrayObject);
        ImGui::Text("VBO ID: %d", m_VertexBufferObject);
        ImGui::Text("VBE ID: %d", m_VertexBufferElement);
        ImGui::Text("Num Indices: %d", m_NumIndices);
		m_Mesh.OnDrawDebug(m_CurrentDrawMode);
		if (ImGui::CollapsingHeader("FrameDataRecords"))
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
		ImGui::PushID((int)this);
		if (ImGui::BeginCombo("Current Draw Mode", m_CurrentDrawMode == DrawMode::Arrays ? "Arrays" : "Elements"))
		{
			for (int i = 0; i < 2; i++)
			{
				const DrawMode drawMode = static_cast<DrawMode>(i);
				const bool isSelected = drawMode == m_CurrentDrawMode;

				if (ImGui::Selectable(drawMode == DrawMode::Arrays ? "Arrays" : "Elements", isSelected))
				{
					m_CurrentDrawMode = drawMode;
					std::vector<float> meshData = m_Mesh.MakeGLData(m_CurrentDrawMode);
					glDeleteBuffers(1, &m_VertexBufferObject);

					//Generates buffer to store vertices
					glGenBuffers(1, &m_VertexBufferObject);

					//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

					//1. Bind Vertex Array Object
					glBindVertexArray(m_VertexArrayObject);

					//2. Copy our vertices array in a buffer for OpenGL to use
					glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
					const GLintptr meshDataSize = meshData.size() * sizeof(float);
					glBufferData(GL_ARRAY_BUFFER, meshDataSize, meshData.data(), GL_STATIC_DRAW);

					//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
					//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
					glBindVertexArray(0);
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
		if (const Shader::RecordData* records = m_Shader->GetRecordData(this))
		{
			if (ImGui::BeginTable("Records", 3, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("Name");
				ImGui::TableSetupColumn("Type");
				ImGui::TableSetupColumn("Value");
				ImGui::TableHeadersRow();
				for (const auto& pair : records->m_Data)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::TextColored(ImGUIUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.first.c_str());
					ImGui::TableSetColumnIndex(1);
					ImGui::TextColored(ImGUIUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.second.m_Type.c_str());
					ImGui::TableSetColumnIndex(2);
					ImGui::TextColored(ImGUIUtils::GetShaderVariableTypeColor(pair.second.m_Type), "%s", pair.second.m_Value.c_str());
				}
				ImGui::EndTable();
			}
		}
	}
#endif //FORGE_DEBUG_ENABLED
}