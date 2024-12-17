#include "engine/core/ManagedObject.h"

namespace ForgeEngine
{
    ManagedObject::ManagedObject() :
        Mother()
    {
    }

    void ManagedObject::SetActive(bool active)
    {
        m_IsActive = active;
        if (m_IsActive)
        {
            OnActivate();
        }
        else
        {
            OnDeactivate();
        }
    }
}