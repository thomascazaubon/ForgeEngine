#include "GameHandler.h"

#include "engine/core/ForgeEngine.h"
#include "engine/debug/ImGUI.h"
#include "engine/render/Color.h"
#include "engine/render/ShaderUtils.h"

#include <chrono>
#include <cmath>
#include <iostream>

namespace ForgeEngine
{
    GameHandler* GameHandler::s_Instance{};

    GameHandler::GameHandler(std::string name, unsigned int width, unsigned int height) :
        m_WindowWidth(width),
        m_WindowHeight(height)
    {
        if (s_Instance == nullptr)
        {
            s_Instance = this;
            m_Window = InitWindow(name, width, height);
            if (m_Window == nullptr)
            {
                std::cout << "ERROR::GAMEHANDLER::CANNOT_CREATE_WINDOW" << std::endl;
                exit(-1);
            }
        }
        else
        {
            std::cout << "ERROR::GAMEHANDLER::HANDLER_ALREADY_EXISTING" << std::endl;
            exit(-1);
        }
    }

	void GameHandler::HandleProcess()
	{
		using ns = std::chrono::nanoseconds;

		std::chrono::time_point<std::chrono::high_resolution_clock> frameStart = std::chrono::high_resolution_clock::now();
		std::chrono::time_point<std::chrono::high_resolution_clock> frameEnd = std::chrono::high_resolution_clock::now();

		float dT{};
		const float nanoToSecMultiplier = (float)std::pow(10, 9);

		if (m_Window != nullptr)
		{
			OnPreInit();
			m_World.PreInit();
			OnInit();
			m_World.Init();
			m_World.PostInit();
			OnPostInit();

			while (!ShouldTerminate())
			{
				//deltaTime is defined using seconds
				dT = std::chrono::duration_cast<ns>(frameEnd - frameStart).count() / nanoToSecMultiplier;
				frameStart = std::chrono::high_resolution_clock::now();

				m_World.PreUpdate(dT);
				OnPreUpdate(dT);
                m_World.Update(dT);
				OnUpdate(dT);
                m_World.PostUpdate(dT);
				OnPostUpdate(dT);

				// feed inputs to dear imgui, start new frame
				#ifdef FORGE_DEBUG_ENABLED
					ImGui_ImplOpenGL3_NewFrame();
					ImGui_ImplGlfw_NewFrame();
					ImGui::NewFrame();
					if (ImGui::BeginMainMenuBar())
					{
						if (ImGui::BeginMenu("File"))
						{
							ImGui::EndMenu();
						}
						if (ImGui::BeginMenu("Edit"))
						{
							if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
							if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
							ImGui::Separator();
							if (ImGui::MenuItem("Cut", "CTRL+X")) {}
							if (ImGui::MenuItem("Copy", "CTRL+C")) {}
							if (ImGui::MenuItem("Paste", "CTRL+V")) {}
							ImGui::EndMenu();
						}
						ImGui::EndMainMenuBar();
					}

					m_World.DrawDebug(dT);

					// Render dear imgui into screen
					ImGui::Render();
					ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				#endif // FORGE_DEBUG_ENABLED

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				glfwSwapBuffers(m_Window);
				glfwPollEvents();

				frameEnd = std::chrono::high_resolution_clock::now();
			}

			OnTermination();
		}
	}

	void GameHandler::OnPreUpdate(float dT)
	{
		ShaderUtils::ClearScreen(COLOR_GREEN);
	}

	void GameHandler::OnTermination()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}
}