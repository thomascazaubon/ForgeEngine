#pragma once

#include "engine/components/Component.h"
#include "engine/render/Color.h"
#include "engine/render/Mesh.h"

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
			void InitRender();

#ifdef FORGE_DEBUG_ENABLED
			void UpdateDrawModeCombo() const;
#endif //FORGE_DEBUG_ENABLED

            Mesh m_Mesh{};
            std::shared_ptr<Shader> m_Shader{};

            unsigned int m_VertexArrayObject{};
			mutable unsigned int m_VertexBufferObject{};
			unsigned int m_VertexBufferElement{};
            unsigned int m_NumIndices{};
			BillboardMode m_BillboardMode;
			mutable DrawMode m_CurrentDrawMode{ DrawMode::Arrays };
	};
}