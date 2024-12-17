#include "Object.h"

namespace ForgeEngine
{
    /*static*/ ObjectID Object::s_LastGivenID{};

    Object::Object() :
        m_ID{ ++s_LastGivenID }
    {
    }
}