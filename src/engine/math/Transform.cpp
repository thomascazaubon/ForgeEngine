#include "Transform.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/debug/ImGUI.h"
#include "engine/render/Color.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    void Transform::DebugImGUI() const
    {
        ImGui::Text("Position: (%.2f, %.2f, %.2f)", m_Position.x, m_Position.y, m_Position.z);
        ImGui::Text("Rotation: (%.2f, %.2f, %.2f)", m_Rotation.x, m_Rotation.y, m_Rotation.z);
        ImGui::Text("Scale: (%.2f, %.2f, %.2f)", m_Scale.x, m_Scale.y, m_Scale.z);
    }

    void Transform::Draw() const
    {
        DebugUtils::DrawLine(GetPosition(), GetPosition() + VECTOR3_UP, COLOR_GREEN);
        DebugUtils::DrawLine(GetPosition(), GetPosition() + VECTOR3_FORWARD, COLOR_BLUE);
        DebugUtils::DrawLine(GetPosition(), GetPosition() + VECTOR3_RIGHT, COLOR_RED);
    }
#endif //FORGE_DEBUG_ENABLED

    void Transform::Update()
    {
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
        }
    }

    const Vector3& Transform::GetPosition() const
    {
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Position;
    }

    const Vector3& Transform::GetRotation() const
    {
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Rotation;
    }

    const Vector3& Transform::GetScale() const
    {
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Scale;
    }

    void Transform::Reset()
    {
        m_Matrix = Matrix4{ 1 };
        m_Dirty = true;
    }

    void Transform::SetPosition(const Vector3& position)
    {
        m_Matrix[3][0] = position.x;
        m_Matrix[3][1] = position.y;
        m_Matrix[3][2] = position.z;
        m_Dirty = true;
    }

    void Transform::SetRotation(const Vector3& rotation)
    {
        m_Dirty = true;
    }

    void Transform::SetScale(const Vector3& scale)
    {
        m_Dirty = true;
    }

    void Transform::Translate(const Vector3& vector)
    {
        ForgeMaths::Translate(m_Matrix, vector);
        m_Dirty = true;
    }

    void Transform::Rotate(float angle, const Vector3& axis)
    {
        ForgeMaths::Rotate(m_Matrix, angle, axis);
        m_Dirty = true;
    }

    void Transform::Rotate(const Vector3& euleurAngles)
    {
        Rotate(euleurAngles.x, VECTOR3_RIGHT);
        Rotate(euleurAngles.y, VECTOR3_UP);
        Rotate(euleurAngles.z, VECTOR3_FORWARD);
        m_Dirty = true;
    }

    void Transform::Scale(const Vector3& scale)
    {
        ForgeMaths::Scale(m_Matrix, scale);
        m_Dirty = true;
    }

    void Transform::Scale(float scale)
    {
        ForgeMaths::Scale(m_Matrix, scale);
        m_Dirty = true;
    }
}