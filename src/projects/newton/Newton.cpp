#include "Newton.h"

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

/*
int main()
{
    Newton::Newton instance("Newton", 1280, 720);
    instance.HandleProcess();
}
*/

namespace Newton
{
    Newton::Newton(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Newton::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        Entity* player = world.RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(0.f, 1.8f, 0.f));

        Entity* ground = world.RegisterEntity();
        ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(1.f), "assets\\shaders\\emissive"));
        Entity* slope = world.RegisterEntity();
        slope->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(1.f), "assets\\shaders\\emissive"));
        Entity* cube = world.RegisterEntity();
        cube->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f), "assets\\shaders\\emissive"));
        cube->GetTransform().Translate(VECTOR3_UP * 0.5f);
        slope->GetTransform().Rotate(Vector3(30.f, 0.f, 0.f));
        slope->GetTransform().Scale(Vector3(10.f, 1.f, 5.f));
    }

    void Newton::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
    }

    void Newton::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Newton::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}