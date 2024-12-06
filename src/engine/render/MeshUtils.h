#pragma once

#include "engine/render/Mesh.h"

namespace ForgeEngine
{
    namespace MeshUtils
    {
        //TODO: These should return pointers, copying a mesh is super suboptimal
        Mesh MakeCube(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakePlane(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakeSprite(const char* materialPath, float height = 1.f);
        Mesh MakeTriangle(float scale = 1.f, const char* materialPath = nullptr);
        Mesh MakeSphere(float scale = 1.f, const char* materialPath = nullptr);
    }
}
