#include "Daggerfall.h"

#include "engine/components/CameraComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "engine/components/MeshComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/input/InputHelper.h"
#include "engine/render/Color.h"
#include "engine/render/MeshUtils.h"
#include "engine/render/ShaderUtils.h"
#include "engine/render/Texture.h"
#include "engine/worldcomponents/InputManager.h"
#include "engine/worldcomponents/DebugManager.h"

void mained()
{
    Daggerfall::Daggerfall instance("Daggerfall", 1280, 720);
    instance.HandleProcess();
}

namespace Daggerfall
{
    Daggerfall::Daggerfall(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Daggerfall::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        Entity* player = world.RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(0.f, 1.8f, 0.f));

        Entity* ground = world.RegisterEntity();
        ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(10.f), "assets\\shaders\\textured"));
    }

    void Daggerfall::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
    }

    void Daggerfall::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Daggerfall::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}