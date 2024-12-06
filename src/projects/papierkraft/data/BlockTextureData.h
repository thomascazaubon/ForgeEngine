#pragma once

#include "engine/core/Object.h"
#include "engine/render/Texture.h"

#include <memory>
#include <string>
#include <utility>

using namespace ForgeEngine;

namespace PapierKraft
{
	//COLUMN INDEX - LINE INDEX
	//ORIGIN IS BOTTOM LEFT 
	using TextureCoordinates = std::pair<unsigned int, unsigned int>;

	#define TEXTURE_GRASS_SIDE			TextureCoordinates{1, 15}
	#define TEXTURE_GRASS_TOP			TextureCoordinates{2, 15}
	#define TEXTURE_GRASS_BOTTOM		TextureCoordinates{0, 15}

	#define TEXTURE_DIRT_UNIFORM		TextureCoordinates{0, 15}

	#define TEXTURE_SAND_UNIFORM		TextureCoordinates{5, 15}

	#define TEXTURE_STONE_UNIFORM		TextureCoordinates{6, 15}

	#define TEXTURE_LOG_SIDE			TextureCoordinates{3, 15}
	#define TEXTURE_LOG_TOP_BOTTOM		TextureCoordinates{4, 15}

	class BlockTextureData : Object
	{
		using Mother = Object;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			TextureCoordinates m_SideTextureCoordinates{};
			TextureCoordinates m_TopTextureCoordinates{};
			TextureCoordinates m_BottomTextureCoordinates{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockTextureData(const TextureCoordinates& sideTextureCoordinates, const TextureCoordinates& topTextureCoordinates, const TextureCoordinates& bottomTextureCoordinates);
			BlockTextureData(const TextureCoordinates& sideTextureCoordinates, const TextureCoordinates& topBottomTextureCoordinates);
			BlockTextureData(const TextureCoordinates& uniformTextureCoordinates);

            //TODO: fix this
#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "TODO"; }
#endif //FORGE_DEBUG_ENABLED

			TextureCoordinates GetSideTexture() const { return m_SideTextureCoordinates; }
			TextureCoordinates GetTopTexture() const { return m_TopTextureCoordinates; }
			TextureCoordinates GetBottomTexture() const { return m_BottomTextureCoordinates; }
	};
}
