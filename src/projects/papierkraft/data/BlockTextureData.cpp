#include "BlockTextureData.h"

namespace PapierKraft
{
    BlockTextureData::BlockTextureData(const TextureCoordinates& sideTextureCoordinates, const TextureCoordinates& topTextureCoordinates, const TextureCoordinates& bottomTextureCoordinates) :
        Mother(),
        m_SideTextureCoordinates(sideTextureCoordinates),
        m_TopTextureCoordinates(topTextureCoordinates),
        m_BottomTextureCoordinates(bottomTextureCoordinates)
    {
    }

    BlockTextureData::BlockTextureData(const TextureCoordinates& sideTextureCoordinates, const TextureCoordinates& topBottomTextureCoordinates) :
        Mother(),
        m_SideTextureCoordinates(sideTextureCoordinates),
        m_TopTextureCoordinates(topBottomTextureCoordinates),
        m_BottomTextureCoordinates(topBottomTextureCoordinates)
    {
    }

    BlockTextureData::BlockTextureData(const TextureCoordinates& uniformTextureCoordinates) :
        Mother(),
        m_SideTextureCoordinates(uniformTextureCoordinates),
        m_TopTextureCoordinates(uniformTextureCoordinates),
        m_BottomTextureCoordinates(uniformTextureCoordinates)
    {
    }
}