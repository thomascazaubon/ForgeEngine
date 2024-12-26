#include "papierkraft.h"

#include "common/components/FirstPersonControllerComponent.h"

#include "engine/components/CameraComponent.h"
#include "engine/input/InputHelper.h"
#include "engine/worldcomponents/DebugManager.h"
#include "engine/worldcomponents/InputManager.h"
#include "engine/render/Color.h"
#include "engine/render/ShaderUtils.h"

#include "projects/papierkraft/components/BlockComponent.h"
#include "projects/papierkraft/components/ChunkComponent.h"
#include "projects/papierkraft/worldcomponents/BlockTextureManager.h"
/*
int main()
{
    PapierKraft::PapierKraft instance("PapierKraft", 1280, 720);
    instance.HandleProcess();
}
*/

namespace PapierKraft
{
    PapierKraft::PapierKraft(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void PapierKraft::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        world.RegisterComponent(new BlockTextureManager());

        Entity* block = world.RegisterEntity();
        block->RegisterComponent(new BlockComponent(EBlockType::Grass));

        Entity* camera = world.RegisterEntity();
        camera->GetTransform().SetPosition(Vector3(0.f, 0.f, 10.f));
        camera->RegisterComponent(new FirstPersonControllerComponent());
        camera->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
    }

    void PapierKraft::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
    }

    void PapierKraft::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool PapierKraft::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}