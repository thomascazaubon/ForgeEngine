#pragma once

#ifdef FORGE_DEBUG_ENABLED
#include "engine/worldcomponents/WorldComponent.h"
#include "engine/math/Vector3.h"

namespace ForgeEngine
{
	class Color;
	class DebugDrawer;

    //TODO: This should probably not be a component
	class DebugManager : public WorldComponent
	{
		using Mother = WorldComponent;

        public:
			DebugManager();
			~DebugManager();

			bool OnInit() override;
            void OnUpdate(float dT) override;
            void OnPostUpdate(float dT) override;

			void OnDrawDebug(float dT) const override;
            const char* GetDebugName() const override { return "DebugManager"; }

            bool IsFreeMouseEnabled() const { return m_FreeMouseEnabled; }
            bool IsImGUIEnabled() const { return m_ImGUIEnabled; }

			void CreateLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration);

		private:
			void ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
			void ToggleFreeMouse();

			DebugDrawer* m_DebugDrawer{ nullptr };
            static const unsigned int K_NB_FRAMERATE_SAMPLES{ 10 };
            int m_CurrentDrawMode;
            int m_FrameRate;
            bool m_FreeMouseEnabled{ false };
            bool m_ImGUIEnabled{ false };
	};
}

#endif //FORGE_DEBUG_ENABLED