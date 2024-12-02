#pragma once

#include "engine/core/WorldComponent.h"
#include "projects/papierkraft/data/BlockTextureData.h"

#include <memory>
#include <unordered_map>

namespace ForgeEngine
{
	class Texture;
}

using namespace ForgeEngine;

namespace PapierKraft
{
	enum class EBlockType;

	#define TEXTURE_ATLAS_PATH "assets\\textures\\blocks\\texture_atlas.png"
	#define BLOCK_TEXTURE_RESOLUTION 16.f

	class BlockTextureManager : public WorldComponent
	{
		using Mother = WorldComponent;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unique_ptr<Texture> m_TextureAtlas{};
			std::unordered_map<EBlockType, std::unique_ptr<BlockTextureData>> m_RegisteredTextures{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockTextureManager();

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "BlockTextureManager"; }
#endif //FORGE_DEBUG_ENABLED

			BlockTextureData* GetTextureDataByBlockType(EBlockType blockType) const;
			Texture* GetTextureAtlas() const { return m_TextureAtlas.get(); }
	};
}