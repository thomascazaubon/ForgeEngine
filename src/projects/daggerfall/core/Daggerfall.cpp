#include "Daggerfall.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/components/MeshComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/helpers/MeshUtils.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/DebugManager.h"

#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"

#include "system/misc/Color.h"

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