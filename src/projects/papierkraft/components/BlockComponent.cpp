#include "BlockComponent.h"

#include "common/components/ViewerComponent.h"
#include "engine/components/MeshComponent.h"
#include "engine/core/Entity.h"
#include "engine/core/World.h"
#include "engine/render/Texture.h"
#include "projects/papierkraft/data/BlockTextureData.h"
#include "projects/papierkraft/worldcomponents/BlockTextureManager.h"

#include <utility>
#include <vector>

using namespace ForgeEngine;

namespace PapierKraft
{
	BlockComponent::BlockComponent(EBlockType blockType) :
		Mother(),
		m_BlockType(blockType)
	{
	}

	bool BlockComponent::OnPreInit() /*override*/
	{
		bool success = Mother::OnPreInit();
        m_TextureData = GetOwner()->GetWorld().GetComponentByType<BlockTextureManager>()->GetTextureDataByBlockType(m_BlockType);
        //TODO: Fix this
        //m_Shader = GetOwner()->GetWorld().GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Textured);
		BuildBlock();
		return success;
	}

	void BlockComponent::BuildBlock()
	{
		using FaceTextureCoordinates = std::pair<float, float>;

		Texture* textureAtlas = GetOwner()->GetWorld().GetComponentByType<BlockTextureManager>()->GetTextureAtlas();
		TextureCoordinates sideTextureCoordinates = m_TextureData->GetSideTexture();
		TextureCoordinates topTextureCoordinates = m_TextureData->GetTopTexture();
		TextureCoordinates bottomTextureCoordinates = m_TextureData->GetBottomTexture();

		float blockTextureLength = BLOCK_TEXTURE_RESOLUTION / textureAtlas->GetWidth();

		//SIDE TEXTURE COORDINATES

		FaceTextureCoordinates sideTextureTopRight
		{
			(sideTextureCoordinates.first + 1) * blockTextureLength,
			(sideTextureCoordinates.second + 1) * blockTextureLength
		};
		FaceTextureCoordinates sideTextureBottomRight
		{
			(sideTextureCoordinates.first + 1) * blockTextureLength,
			(sideTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates sideTextureBottomLeft
		{
			(sideTextureCoordinates.first) * blockTextureLength,
			(sideTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates sideTextureTopLeft
		{
			(sideTextureCoordinates.first) * blockTextureLength,
			(sideTextureCoordinates.second + 1) * blockTextureLength
		};

		// TOP TEXTURE COORDINATES

		FaceTextureCoordinates topTextureTopRight
		{
			(topTextureCoordinates.first + 1) * blockTextureLength,
			(topTextureCoordinates.second + 1) * blockTextureLength
		};
		FaceTextureCoordinates topTextureBottomRight
		{
			(topTextureCoordinates.first + 1) * blockTextureLength,
			(topTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates topTextureBottomLeft
		{
			(topTextureCoordinates.first) * blockTextureLength,
			(topTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates topTextureTopLeft
		{
			(topTextureCoordinates.first) * blockTextureLength,
			(topTextureCoordinates.second + 1) * blockTextureLength
		};

		// BOTTOM TEXTURE COORDINATES

		FaceTextureCoordinates bottomTextureTopRight
		{
			(bottomTextureCoordinates.first + 1) * blockTextureLength,
			(bottomTextureCoordinates.second + 1) * blockTextureLength
		};
		FaceTextureCoordinates bottomTextureBottomRight
		{
			(bottomTextureCoordinates.first + 1) * blockTextureLength,
			(bottomTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates bottomTextureBottomLeft
		{
			(bottomTextureCoordinates.first) * blockTextureLength,
			(bottomTextureCoordinates.second) * blockTextureLength
		};
		FaceTextureCoordinates bottomTextureTopLeft
		{
			(bottomTextureCoordinates.first) * blockTextureLength,
			(bottomTextureCoordinates.second + 1) * blockTextureLength
		};

		std::vector<float> verticesTexturesCoordinates{
			/******************SIDE FRONT*******************/
				// positions       // texture coords
			 0.5f,  0.5f, 0.5f,   sideTextureTopRight.first,		sideTextureTopRight.second, // top right
			 0.5f, -0.5f, 0.5f,   sideTextureBottomRight.first,		sideTextureBottomRight.second, // bottom right
			-0.5f, -0.5f, 0.5f,   sideTextureBottomLeft.first,		sideTextureBottomLeft.second, // bottom left
			-0.5f,  0.5f, 0.5f,   sideTextureTopLeft.first,			sideTextureTopLeft.second,  // top left 
			/******************SIDE RIGHT*******************/
				// positions       // texture coords
			 0.5f,  0.5f,-0.5f,   sideTextureTopRight.first,		sideTextureTopRight.second, // top right
			 0.5f, -0.5f,-0.5f,   sideTextureBottomRight.first,		sideTextureBottomRight.second, // bottom right
			 0.5f, -0.5f, 0.5f,   sideTextureBottomLeft.first,		sideTextureBottomLeft.second, // bottom left
			 0.5f,  0.5f, 0.5f,   sideTextureTopLeft.first,			sideTextureTopLeft.second,  // top left 
			 /******************SIDE BACK********************/
				// positions       // texture coords
			-0.5f,  0.5f,-0.5f,   sideTextureTopRight.first,		sideTextureTopRight.second, // top right
			-0.5f, -0.5f,-0.5f,   sideTextureBottomRight.first,		sideTextureBottomRight.second, // bottom right
			 0.5f, -0.5f,-0.5f,   sideTextureBottomLeft.first,		sideTextureBottomLeft.second, // bottom left
			 0.5f,  0.5f,-0.5f,   sideTextureTopLeft.first,			sideTextureTopLeft.second,  // top left 
			/******************SIDE LEFT********************/
				// positions       // texture coords
			-0.5f,  0.5f, 0.5f,   sideTextureTopRight.first,		sideTextureTopRight.second, // top right
			-0.5f, -0.5f, 0.5f,   sideTextureBottomRight.first,		sideTextureBottomRight.second, // bottom right
			-0.5f, -0.5f,-0.5f,   sideTextureBottomLeft.first,		sideTextureBottomLeft.second, // bottom left
			-0.5f,  0.5f,-0.5f,   sideTextureTopLeft.first,			sideTextureTopLeft.second,  // top left 
			/******************TOP**************************/
				// positions       // texture coords
			 0.5f, 0.5f, -0.5f,    topTextureTopRight.first,		topTextureTopRight.second, // top right
			 0.5f, 0.5f,  0.5f,    topTextureBottomRight.first,		topTextureBottomRight.second, // bottom right
			-0.5f, 0.5f,  0.5f,    topTextureBottomLeft.first,		topTextureBottomLeft.second, // bottom left
			-0.5f, 0.5f, -0.5f,    topTextureTopLeft.first,			topTextureTopLeft.second,  // top left 
			/******************BOTTOM***********************/
				// positions       // texture coords
			-0.5f, -0.5f, -0.5f,   bottomTextureTopRight.first,		bottomTextureTopRight.second, // top right
			-0.5f, -0.5f,  0.5f,   bottomTextureBottomRight.first,	bottomTextureBottomRight.second, // bottom right
			 0.5f, -0.5f,  0.5f,   bottomTextureBottomLeft.first,	bottomTextureBottomLeft.second, // bottom left
			 0.5f, -0.5f, -0.5f,   bottomTextureTopLeft.first,		bottomTextureTopLeft.second,  // top left 
		};

		//Coordinate indexes 
		std::vector<unsigned int> coordinates = {
			/******************SIDE FRONT*******************/
					0, 1, 3,
					1, 2, 3,
			/******************SIDE RIGHT*******************/
					4, 5, 7,
					5, 6, 7,
			/******************SIDE BACK********************/
					8, 9, 11,
					9, 10,11,
			/******************SIDE LEFT********************/
					12, 13, 15,
					13, 14, 15,
			/******************TOP**************************/
					16, 17, 19,
					17, 18, 19,
			/******************BOTTOM***********************/
					20, 21, 23,
					21, 22, 23
		};

        //TODO: FIX THIS
		//GetOwner()->RegisterComponent(new MeshComponent(verticesTexturesCoordinates, coordinates, m_Shader, textureAtlas));
	}
}