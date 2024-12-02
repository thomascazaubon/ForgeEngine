#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class Shader;
	class Texture;
}

using namespace ForgeEngine;

namespace PapierKraft
{
	class BlockTextureData;

	enum class EBlockType
	{
		Dirt = 0,
		Grass,
		Stone,
		Woodlog,
		Sand,
		None,
		Count
	};

	class BlockComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			EBlockType m_BlockType;
			BlockTextureData* m_TextureData{};
			Shader* m_Shader{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockComponent(EBlockType blockType);

			virtual bool OnPreInit() override;

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "BlockComponent"; }
#endif //FORGE_DEBUG_ENABLED

		private:
			void BuildBlock();
	};
}