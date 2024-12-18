#pragma once

#include "engine/components/Component.h"
#include "engine/render/Color.h"
#include "engine/render/Mesh.h"

#include <map>
#include <memory>
#include <string>

namespace ForgeEngine
{
	class Shader;
	class Texture;

	enum class BillboardMode
	{
		Disabled,
		LockY,
		Full
	};

	class MeshComponent : public Component
	{
		using Mother = Component;

		public:
			MeshComponent(const Mesh& mesh, const std::string& shaderPath, BillboardMode billboardMode = BillboardMode::Disabled);

			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate(float dT) override;
			virtual void OnDestroy() override;

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "MeshComponent"; }
#endif //FORGE_DEBUG_ENABLED

            Mesh& GetMesh() { return m_Mesh; }

		protected:
#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug(float dT) const override;
#endif //FORGE_DEBUG_ENABLED

		private:
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

            void UpdateDrawModeCombo() const;
            void DebugShaderRecords() const;

            void SetShaderFloat(const char* which, float value);
            void SetShaderBool(const char* which, bool value);
            void SetShaderInt(const char* which, int value);
            void SetShaderColor(const char* which, const Color& value);
            void SetShaderTexture(const char* which, const Texture* texture);
            void SetShaderMatrix4(const char* which, const glm::mat4& matrix);
            void SetShaderMatrix3(const char* which, const glm::mat3& matrix);
            void SetShaderVector3(const char* which, const Vector3& vector);
            void SetShaderMaterial(const char* which, const Material& material);
#endif //FORGE_DEBUG_ENABLED

            void ResetRender();
            void InitRender();

            Mesh m_Mesh{};
            std::shared_ptr<Shader> m_Shader{};

            unsigned int m_VertexArrayObject{};
			mutable unsigned int m_VertexBufferObject{};
			unsigned int m_VertexBufferElement{};
            unsigned int m_NumIndices{};
			BillboardMode m_BillboardMode;
			mutable DrawMode m_CurrentDrawMode{ DrawMode::Arrays };

#ifdef FORGE_DEBUG_ENABLED
			mutable RecordData m_RecordData;
			mutable bool m_RecordEnabled{false};
			mutable bool m_ResetRequested{false};
#endif //FORGE_DEBUG_ENABLED
	};
}