#include "BasicGameHandler.h"

#include "common/worldcomponents/SkyboxComponent.h"
#include "engine/assetloaders/Animation2DLoader.h"
#include "engine/assetloaders/Animator2DLoader.h"
#include "engine/assetloaders/MaterialLoader.h"
#include "engine/assetloaders/ShaderLoader.h"
#include "engine/assetloaders/TextureLoader.h"
#include "engine/render/ShaderUtils.h"
#include "engine/worldcomponents/InputManager.h"
#include "engine/worldcomponents/LightManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/ImGUICore.h"
#include "engine/worldcomponents/DebugManager.h"
#endif //FORGE_DEBUG_ENABLED

namespace ForgeEngine
{
    void BasicGameHandler::OnPreInit() /*override*/
    {
        Mother::OnPreInit();

        m_World.RegisterComponent(new ShaderLoader());
        m_World.RegisterComponent(new MaterialLoader());
        m_World.RegisterComponent(new TextureLoader());
        m_World.RegisterComponent(new Animation2DLoader());
        m_World.RegisterComponent(new Animator2DLoader());
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

    void BasicGameHandler::OnUpdatePreRender(float dT) /*override*/
    {
        Mother::OnUpdatePreRender(dT);
        ShaderUtils::ClearScreen(m_World.GetComponentByType<SkyboxComponent>()->GetCurrentSkyColor());
    }

    bool BasicGameHandler::ShouldTerminate()
    {
        return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    }
}
