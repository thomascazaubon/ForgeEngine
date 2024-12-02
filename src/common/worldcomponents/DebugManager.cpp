#include "DebugManager.h"

#include "common/helpers/InputHelper.h"
#include "engine/core/ForgeEngine.h"
#include "engine/ui/ImGUI.h"

#include <list>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
	DebugManager::DebugManager() :
		m_CurrentDrawMode(GL_FILL)
	{
        glPolygonMode(GL_FRONT_AND_BACK, m_CurrentDrawMode);
	}

    void DebugManager::OnUpdate(float dT) /*override*/
    {
        ProcessDebugInput();
        ComputeFramerate(dT);
    }

	void DebugManager::OnDrawDebug(float dT) const  /*override*/
	{
		ImGui::Text("FPS: %d", m_FrameRate);
		ImGui::Text("Window Size: %d x %d", GameHandler::Get().GetWindowWidth(), GameHandler::Get().GetWindowHeight());
		Vector2 mousePosition = InputHelper::GetMousePosition();
		ImGui::Text("Mouse {%d,%d}", static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y));
	}

	void DebugManager::ComputeFramerate(float dT)
	{
		static std::list<float> deltaTimes;
		float framerate = 0;

		if (deltaTimes.size() == K_NB_FRAMERATE_SAMPLES)
		{
			deltaTimes.pop_back();
		}
		deltaTimes.push_front(dT);

		for (auto it = deltaTimes.begin(); it != deltaTimes.end(); it++)
		{
			framerate += *it;
		}

        m_FrameRate = static_cast<int>(1 / (framerate / deltaTimes.size()));
	}

	void DebugManager::ProcessDebugInput()
	{
		if (InputHelper::IsInputActive(EInputAction::ToggleWireframe))
		{
			ToggleWireframeMode();
		}
        if (InputHelper::IsInputActive(EInputAction::ToggleFreeMouse))
        {
            ToggleFreeMouse();
        }
        if (InputHelper::IsInputActive(EInputAction::ToggleImGUI))
        {
            m_ImGUIEnabled = m_ImGUIEnabled ? false : true;
        }
	}

    void DebugManager::ToggleFreeMouse()
    {
        if (!m_FreeMouseEnabled)
        {
            m_FreeMouseEnabled = true;
            glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            m_FreeMouseEnabled = false;
            glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

	void DebugManager::ToggleWireframeMode()
	{
		int newDrawMode = ((m_CurrentDrawMode == GL_LINE) ? GL_FILL : GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, newDrawMode);
		m_CurrentDrawMode = newDrawMode;
	}
#endif //FORGE_DEBUG_ENABLED
}
