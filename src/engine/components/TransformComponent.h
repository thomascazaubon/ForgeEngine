#pragma once

#include "engine/core/Component.h"
#include "system/math/Matrix4.h"
#include "system/math/Vector3.h"

namespace ForgeEngine
{
	class TransformComponent : public Component
	{
		using Mother = Component;

        public:
            TransformComponent();

#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug(float dT) const override;

            const char* GetDebugName() const override { return "TransformComponent"; }
#endif //FORGE_DEBUG_ENABLED

            const Matrix4& GetMatrix() const { return m_Matrix; }

            const Vector3& GetPosition() const;
            const Vector3& GetRotation() const;
            const Vector3& GetScale() const;

            void SetPosition(const Vector3& position);
            void SetRotation(const Vector3& rotation);
            void SetScale(const Vector3& scale);

            void Translate(const Vector3& vector);
            void Rotate(float angle, const Vector3& axis);
            void Rotate(const Vector3& euleurAngles);
            void Scale(const Vector3& scale);
            void Scale(float scale);

            void Reset();

		private:
			Matrix4 m_Matrix;

			mutable Vector3 m_Position{0.f};
			mutable Vector3 m_Rotation{0.f};
			mutable Vector3 m_Scale{1.f};

            mutable bool m_Dirty{ true };
	};
}