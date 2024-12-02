#include "GameHandler.h"

#include "common/worldcomponents/DebugManager.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/LightManager.h"
#include "common/worldcomponents/MaterialLoader.h"
#include "common/worldcomponents/ShaderLoader.h"
#include "common/worldcomponents/TextureLoader.h"

#include "engine/core/ForgeEngine.h"
#include "engine/shader/ShaderUtils.h"
#include "engine/ui/ImGUI.h"

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
			OnInit();

			m_World.PreInit();
			m_World.Init();
			m_World.PostInit();

			while (!ShouldTerminate())
			{
				//deltaTime is defined using seconds
				dT = std::chrono::duration_cast<ns>(frameEnd - frameStart).count() / nanoToSecMultiplier;
				frameStart = std::chrono::high_resolution_clock::now();

				OnUpdate(dT);

				m_World.PreUpdate(dT);
                m_World.Update(dT);
                m_World.PostUpdate(dT);

				// feed inputs to dear imgui, start new frame
				#ifdef FORGE_DEBUG_ENABLED
					ImGui_ImplOpenGL3_NewFrame();
					ImGui_ImplGlfw_NewFrame();
					ImGui::NewFrame();

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

	void GameHandler::OnInit()
	{
        m_World.RegisterComponent(new ShaderLoader());
        m_World.RegisterComponent(new InputManager());
        m_World.RegisterComponent(new LightManager());
        m_World.RegisterComponent(new MaterialLoader());
        m_World.RegisterComponent(new TextureLoader());

		#ifdef FORGE_DEBUG_ENABLED
            m_World.RegisterComponent(new DebugManager());

			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
			ImGui_ImplOpenGL3_Init("#version 150");
		#endif //#ifdef FORGE_DEBUG_ENABLED
	}

	void GameHandler::OnTermination()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	bool GameHandler::ShouldTerminate()
	{
		return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	}
}