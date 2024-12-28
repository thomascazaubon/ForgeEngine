#pragma once

#include "engine/math/Vector3.h">

#include <string>

namespace ForgeEngine
{
    class World;

    namespace CartographUtils
    {
        void LoadMap(World& world, const std::string& filePath, Vector3& spawnPosition);
    }
}