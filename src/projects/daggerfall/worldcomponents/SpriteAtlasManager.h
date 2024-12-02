#pragma once

#include "engine/core/WorldComponent.h"

namespace ForgeEngine
{
    class Texture;
}

using namespace ForgeEngine;

namespace Daggerfall
{
    enum class EBlockType;

#define TEXTURE_ATLAS_PATH "assets\\daggerfall\\textures\\blocks\\texture_atlas.png"
#define BLOCK_TEXTURE_RESOLUTION 16.f

    class SpriteAtlasManager : public WorldComponent
    {
        using Mother = WorldComponent;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

    private:

        /************************************/
        /**************METHODS***************/
        /************************************/

    public:
        SpriteAtlasManager();
    };
}