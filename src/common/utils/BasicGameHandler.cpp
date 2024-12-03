#include "BasicGameHandler.h"

#include "common/worldcomponents/DebugManager.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/LightManager.h"
#include "common/worldcomponents/MaterialLoader.h"
#include "common/worldcomponents/ShaderLoader.h"
#include "common/worldcomponents/SkyboxComponent.h"
#include "common/worldcomponents/TextureLoader.h"
#include "engine/core/ForgeEngine.h"
#include "engine/shader/ShaderUtils.h"

namespace ForgeEngine
{
	void BasicGameHandler::OnInit() /*override*/
	{
		Mother::OnInit();

		m_World.RegisterComponent(new ShaderLoader());
		m_World.RegisterComponent(new InputManager());
		m_World.RegisterComponent(new LightManager());
		m_World.RegisterComponent(new MaterialLoader());
		m_World.RegisterComponent(new TextureLoader());
		m_World.RegisterComponent(new SkyboxComponent(100.f, MAX_LIGHT_TIME_END));

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

	void BasicGameHandler::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);
		ShaderUtils::ClearScreen(m_World.GetComponentByType<SkyboxComponent>()->GetCurrentSkyColor());
	}

	bool BasicGameHandler::ShouldTerminate()
	{
		return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	}
}
