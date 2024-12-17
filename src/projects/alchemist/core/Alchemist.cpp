#include "alchemist.h"

#include "common/components/FirstPersonControllerComponent.h"

#include "engine/components/CameraComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/input/InputHelper.h"
#include "engine/render/Color.h"
#include "engine/render/ShaderUtils.h"
#include "engine/render/Texture.h"
#include "engine/worldcomponents/InputManager.h"
#include "engine/worldcomponents/DebugManager.h"

#include "projects/alchemist/components/LandscapeComponent.h"
/*
int main()
{
    Alchemist::Alchemist instance("Alchemist", ALCHEMIST_WINDOW_WIDTH, ALCHEMIST_WINDOW_HEIGHT);
    instance.HandleProcess();
}
*/
namespace Alchemist
{
    Alchemist::Alchemist(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Alchemist::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        Entity* landscape = world.RegisterEntity();
        landscape->RegisterComponent(new LandscapeComponent());

        Entity* camera = world.RegisterEntity();
        camera->RegisterComponent(new CameraComponent(CameraComponent::OrthographicCamera{ ALCHEMIST_WINDOW_WIDTH, ALCHEMIST_WINDOW_HEIGHT, 0.f, 100.f}));
        camera->GetTransform().SetPosition(Vector3(0.f, 0.f, 1.f));
    }

    void Alchemist::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_WHITE);
    }

    void Alchemist::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Alchemist::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}