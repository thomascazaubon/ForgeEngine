#pragma once

#include "engine/core/Component.h"
#include "engine/misc/Mesh.h"
#include "system/misc/Color.h"

#include <memory>
#include <string>

namespace ForgeEngine
{
	class Shader;
	class Texture;

	class MeshComponent : public Component
	{
		using Mother = Component;

		public:
			MeshComponent(const Mesh& mesh, const std::string& shaderPath);

			virtual void OnUpdate(float dT) override;
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

            Mesh m_Mesh{};
            std::shared_ptr<Shader> m_Shader{};

            unsigned int m_VertexArrayObject{};
			unsigned int m_VertexBufferObject{};
			unsigned int m_VertexBufferElement{};
            unsigned int m_NumIndices{};
	};
}