#include "BasicGameHandler.h"

#include "common/worldcomponents/SkyboxComponent.h"
#include "engine/assetloaders/AnimationLoader.h"
#include "engine/assetloaders/MaterialLoader.h"
#include "engine/assetloaders/ShaderLoader.h"
#include "engine/assetloaders/TextureLoader.h"
#include "engine/core/ForgeEngine.h"
#include "engine/debug/ImGUICore.h"
#include "engine/render/ShaderUtils.h"
#include "engine/worldcomponents/DebugManager.h"
#include "engine/worldcomponents/InputManager.h"
#include "engine/worldcomponents/LightManager.h"

namespace ForgeEngine
{
    void BasicGameHandler::OnPreInit() /*override*/
    {
        Mother::OnPreInit();

        m_World.RegisterComponent(new ShaderLoader());
        m_World.RegisterComponent(new MaterialLoader());
        m_World.RegisterComponent(new TextureLoader());
        m_World.RegisterComponent(new AnimationLoader());
        m_World.RegisterComponent(new InputManager());
        m_World.RegisterComponent(new LightManager());
        m_World.RegisterComponent(new SkyboxComponent(0.f, NOON_TIME));

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

    void BasicGameHandler::OnPreUpdate(float dT) /*override*/
    {
        Mother::OnPreUpdate(dT);
        ShaderUtils::ClearScreen(m_World.GetComponentByType<SkyboxComponent>()->GetCurrentSkyColor());
    }

    bool BasicGameHandler::ShouldTerminate()
    {
        return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    }
}
