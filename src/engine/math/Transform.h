#pragma once

#include "engine/math/Matrix4.h"
#include "engine/math/Vector3.h"

namespace ForgeEngine
{
    class Transform
    {
        public:
    #ifdef FORGE_DEBUG_ENABLED
            void DebugImGUI() const;
            void Draw() const;
    #endif //FORGE_DEBUG_ENABLED

            void Update();

            const Matrix4& GetMatrix() const { return m_Matrix; }

            const Vector3& GetPosition() const;
            const Vector3& GetRotation() const;
            const Vector3& GetScale() const;
            Vector3 GetXAxis() const;
            Vector3 GetYAxis() const;
            Vector3 GetZAxis() const;
            Matrix4 MakeLookAt(const Vector3& direction) const;

            void SetPosition(const Vector3& position);
            void SetRotation(const Vector3& rotation);
            void SetScale(const Vector3& scale);

            void Translate(const Vector3& vector);
            void Rotate(float angle, const Vector3& axis);
            void Rotate(const Vector3& euleurAngles);
            void Scale(const Vector3& scale);
            void Scale(float scale);
            void LookAt(const Vector3& direction);

            void Reset();

        private:
            Matrix4 m_Matrix{ 1 };

            mutable Vector3 m_Position{ 0.f };
            mutable Vector3 m_Rotation{ 0.f };
            mutable Vector3 m_Scale{ 1.f };

            mutable bool m_Dirty{ true };
    };
}