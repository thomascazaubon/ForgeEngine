#pragma once

#include "glm/vec4.hpp"

namespace ForgeEngine
{
    #define Vector4_X Vector3(1.f, 0.f, 0.f, 0.f)
    #define Vector4_Y Vector3(0.f, 1.f, 0.f, 0.f)
    #define Vector4_Z Vector3(0.f, 0.f, 1.f, 0.f)

    #define Vector4_UNIT Vector3(1.f, 1.f, 1.f, 0.f)
    #define Vector4_NULL Vector3(0.f, 0.f, 0.f, 0.f)

    typedef glm::vec4 Vector4;
}