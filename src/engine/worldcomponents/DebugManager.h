#pragma once

#include "engine/worldcomponents/WorldComponent.h"

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    //TODO: This should probably not be a component
	class DebugManager : public WorldComponent
	{
		using Mother = WorldComponent;

        public:
			DebugManager();

            void OnUpdate(float dT) override;

			void OnDrawDebug(float dT) const override;
            const char* GetDebugName() const override { return "DebugManager"; }

            bool IsFreeMouseEnabled() const { return m_FreeMouseEnabled; }
            bool IsImGUIEnabled() const { return m_ImGUIEnabled; }

		private:
			void ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
			void ToggleFreeMouse();

            static const unsigned int K_NB_FRAMERATE_SAMPLES{ 10 };
            int m_CurrentDrawMode;
            int m_FrameRate;
            bool m_FreeMouseEnabled{ false };
            bool m_ImGUIEnabled{ false };
	};
#endif //FORGE_DEBUG_ENABLED
}