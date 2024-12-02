#pragma once

#include "engine/core/Component.h"
#include "system/math/Vector3.h"

using namespace ForgeEngine;

namespace PapierKraft
{
	#define CHUNK_WIDTH 8
	#define CHUNK_HEIGHT 8

	#define DIRT_LAYER_HEIGHT 3

	enum class EBiomeType
	{
		Plain = 0,
		Desert,
		Forest,
		Count
	};

	enum class EBlockType;

	class ChunkComponent : Component
	{
		using Mother = Component;
		using ChunkBlocksArray = EBlockType[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			EBiomeType m_BiomeType;
			ChunkBlocksArray m_Blocks;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			ChunkComponent(EBiomeType biomeType, Vector3 position);
			
            virtual bool OnPreInit() override;

			EBlockType ComputeBlockType(float yCoordinate);
	};
}