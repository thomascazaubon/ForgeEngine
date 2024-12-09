#pragma once

#include "engine/render/Mesh.h"

namespace ForgeEngine
{
    namespace MeshUtils
    {
        //TODO: These should return pointers, copying a mesh is super suboptimal
        Mesh MakeCube(float scale = 1.f, const char* materialPath = nullptr, Pivot pivotType = Pivot::Geometry);
        Mesh MakePlane(float scale = 1.f, const char* materialPath = nullptr, Pivot pivotType = Pivot::Geometry);
        Mesh MakeSprite(const char* materialPath, float height = 1.f, Pivot pivotType = Pivot::Geometry);
        Mesh MakeTriangle(float scale = 1.f, const char* materialPath = nullptr, Pivot pivotType = Pivot::Geometry);
        Mesh MakeSphere(float scale = 1.f, const char* materialPath = nullptr, Pivot pivotType = Pivot::Geometry);
    }
}
