#include "Cartographer.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/input/InputHelper.h"
#include "common/utils/CartographUtils.h"
/*
int main()
{
    Cartographer::Cartographer instance("Cartographer", 1920, 1080);
    instance.HandleProcess();
}
*/
namespace Cartographer
{
    Cartographer::Cartographer(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Cartographer::OnInit() /*override*/
    {
        Mother::OnInit();
        Vector3 spawnPosition = VECTOR3_NULL;

        CartographUtils::LoadMap(GetWorld(), "assets\\maps\\big.map", spawnPosition);

        Entity* player = GetWorld().RegisterEntity("Player");
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(spawnPosition.x, 1.7f, spawnPosition.z));
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