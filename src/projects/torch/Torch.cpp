#include "Torch.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/worldcomponents/SkyboxComponent.h"
#include "engine/components/AnimatorComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/LightComponent.h"
#include "engine/components/MeshComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/debug/DebugUtils.h"
#include "engine/input/InputHelper.h"
#include "engine/render/MeshUtils.h"
#include "engine/render/OpenGL.h"
#include "engine/render/ShaderUtils.h"
#include "engine/worldcomponents/DebugManager.h"
#include "engine/worldcomponents/InputManager.h"

int main()
{
    Torch::Torch instance("Torch", 1920, 1080);
    instance.HandleProcess();
}

namespace Torch
{
    Torch::Torch(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
        , m_Cube(nullptr)
        , m_Light(nullptr)
    {
    }

    void Torch::OnPostInit() /*override*/
    {
        Mother::OnPostInit();
        World& world = GetWorld();
        
        Entity* ground = world.RegisterEntity("Ground");
        ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(100.f, "assets\\materials\\grass.mat"), "assets\\shaders\\lit"));
        
        Entity* player = world.RegisterEntity("Player");
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(2.f, 1.7f, 2.f));
        
        Color lightColor = COLOR_WHITE;
        m_Light = world.RegisterEntity("Light");
        m_Light->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(0.1f, "assets\\materials\\white.mat"), "assets\\shaders\\emissive"));
        m_Light->RegisterComponent(new LightComponent(30.f, 1.f, lightColor));
        m_Light->GetTransform().Translate(VECTOR3_UP * 2.f + VECTOR3_RIGHT * 2.f);

        Entity* cube1 = world.RegisterEntity("MarbleCube");
        cube1->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, "assets\\materials\\marble.mat"), "assets\\shaders\\lit"));
        cube1->GetTransform().Translate(VECTOR3_UP * 1.7f);

        m_Cube = world.RegisterEntity("MarbleCube2");
        m_Cube->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, "assets\\materials\\marble.mat", Pivot::Bottom), "assets\\shaders\\lit"));
        m_Cube->GetTransform().Translate(Vector3(4.f, 0.f, 4.f));

        m_Cube = world.RegisterEntity("NPC");
        m_Cube->RegisterComponent(new MeshComponent(MeshUtils::MakeSprite("assets\\materials\\npc.mat", 1.8, Pivot::Bottom), "assets\\shaders\\billboard"));
        m_Cube->RegisterComponent(new AnimatorComponent("assets\\anims\\npc_walk.anim"));
        m_Cube->GetTransform().SetPosition(Vector3(3.f, 0.f, 3.f));
    }

    void Torch::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        Vector3 position = m_Light->GetPosition();
        m_Light->GetTransform().SetPosition(Vector3(position.x, 2.f + (sin(static_cast<float>(glfwGetTime()) * 2.0f)), position.z));
        const CameraComponent& player = CameraComponent::GetActiveCamera();
        const Vector3& playerPosition = player.GetOwner()->GetPosition();
        const Vector3& playerPositionFlat = Vector3(playerPosition.x, m_Cube->GetPosition().y, playerPosition.z);
        const Vector3 toPlayer = playerPositionFlat - m_Cube->GetPosition();
        if (glm::length(toPlayer) > 3.f)
        {
            m_Cube->GetTransform().Translate(ForgeMaths::Normalize(toPlayer) * 5.f * dT);
        }
       
    }

    void Torch::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Torch::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}