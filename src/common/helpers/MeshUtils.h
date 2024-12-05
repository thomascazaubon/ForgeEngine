#pragma once

#include "engine/misc/Mesh.h"

namespace ForgeEngine
{
    namespace MeshUtils
    {
        Mesh MakeCube(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakePlane(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakeSprite(const char* materialPath, float height = 1.f);
        Mesh MakeTriangle(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakeSphere(float scale = 1.f, const char* materialPath = nullptr);
    }
}
