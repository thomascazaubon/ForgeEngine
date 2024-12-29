#include "Cartographer.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/utils/CartographUtils.h"
#include "engine/components/Animator2DComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/MeshComponent.h"
#include "engine/render/MeshUtils.h"
#include "engine/input/InputHelper.h"
#include "projects/daggerfall/components/NPCComponent.h"

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
        Vector3 spawnPosition = VECTOR3_NULL;

        CartographUtils::LoadMap(GetWorld(), "assets\\maps\\big.map", spawnPosition);

        Entity* player = GetWorld().RegisterEntity("Player");
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->RegisterComponent(new LightComponent(10.f, 0.5f, COLOR_WHITE));
        player->GetTransform().SetPosition(Vector3(spawnPosition.x, 1.7f, spawnPosition.z));

        for (float i = 0.f; i < 1.f; i++)
        {
            Entity* npc = GetWorld().RegisterEntity();
            npc->RegisterComponent(new MeshComponent(MeshUtils::MakeSprite("assets\\materials\\npc.mat", 1.8, Pivot::Bottom), "assets\\shaders\\billboard"));
            npc->RegisterComponent(new Animator2DComponent("assets\\anims\\thief.animator"));
            npc->RegisterComponent(new NPCComponent());
            npc->GetTransform().Translate((VECTOR3_RIGHT * i * 3.f) + (VECTOR3_FORWARD * i * 3.f));
        }
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