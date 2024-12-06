#pragma once

#include "engine/core/ManagedObject.h"

namespace ForgeEngine
{
    class World;

    class WorldComponent : public ManagedObject
    {
        using Mother = ManagedObject;

        friend class World;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

    protected:
        World* m_World{};

        /************************************/
        /**************METHODS***************/
        /************************************/

    public:
        World* GetWorld() const { return m_World; }

    protected:
        void SetWorld(World* world) { m_World = world; }
    };
}