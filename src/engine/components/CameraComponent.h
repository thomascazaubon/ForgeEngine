#pragma once

#include "engine/components/Component.h"
#include "engine/math/Matrix4.h"

namespace ForgeEngine
{
	class CameraComponent : public Component
	{
		using Mother = Component;

		public:
			struct PerspectiveCamera
			{
				float m_Fov = 45.f; 
				float m_AspectRatio = 16.f / 9.f;
				float m_NearPlane = 0.1f;
				float m_FarPlane = 100.f;
			};

			struct OrthographicCamera
			{
				unsigned int m_Width = 1280;
				unsigned int m_Height = 720;
				float m_NearPlane = 0.1f;
				float m_FarPlane = 100.f;
			};

		public:
			CameraComponent(const PerspectiveCamera& cameraData);
			CameraComponent(const OrthographicCamera& cameraData);

			static const CameraComponent& GetActiveCamera() { return *s_ActiveCamera; }
			const Matrix4& GetProjection() const { return m_Projection; }
			const Matrix4& GetView() const { return m_View; }

			virtual void OnUpdate(float dT) override;
			virtual void OnActivate() override;
			virtual void OnDeactivate() override;
			virtual void OnDestroy() override;

#ifdef FORGE_DEBUG_ENABLED
            const char* GetDebugName() const override { return "CameraComponent"; }
#endif //FORGE_DEBUG_ENABLED

			void SetFocusedEntity(const Entity* entity) { m_FocusedEntity = entity; }
			void SetFocusActive(bool active) { m_IsFocusActive = active; }
			float GetYaw() const        { return m_Yaw; }
			void  SetYaw(float yaw)     { m_Yaw = yaw; }
			float GetPitch() const      { return m_Pitch; }
			void  SetPitch(float pitch) { m_Pitch = pitch; }

			Vector3 GetSight()	const { return m_Sight; }
			Vector3 GetRight()	const { return m_Right; }
			Vector3 GetUp()		const { return m_Up; }

		private:
			void ClearActiveCameraIfNeeded();
			void RefreshView();

        public:
            static const CameraComponent* s_ActiveCamera;

        private:
            Matrix4 m_View{};
            Matrix4 m_Projection{};

            const Entity* m_FocusedEntity{};
            bool m_IsFocusActive{ false };

            float m_Yaw{ -90.f };
            float m_Pitch{ 0.f };
            Vector3 m_Sight{};
            Vector3 m_Right{};
            Vector3 m_Up{};
	};
}