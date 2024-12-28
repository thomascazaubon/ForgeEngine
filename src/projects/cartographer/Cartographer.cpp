#include "Cartographer.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "engine/components/Animator2DComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/MeshComponent.h"
#include "engine/input/InputHelper.h"
#include "engine/render/MeshUtils.h"
#include "engine/render/OpenGL.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#include "engine/worldcomponents/DebugManager.h"
#endif //FORGE_DEBUG_ENABLED

int main()
{
    Cartographer::Cartographer instance("Cartographer", 1920, 1080);
    instance.HandleProcess();
}

namespace Cartographer
{
    Cartographer::Cartographer(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Cartographer::OnInit() /*override*/
    {
        Mother::OnInit();
        World& world = GetWorld();

        Entity* ground = world.RegisterEntity("Ground");
        ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(100.f, "assets\\materials\\grass.mat"), "assets\\shaders\\lit"));

        Entity* player = world.RegisterEntity("Player");
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(0.f, 1.7f, 0.f));
    }

    void Cartographer::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Cartographer::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}