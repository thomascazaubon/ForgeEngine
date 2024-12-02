#include "Torch.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/components/LightComponent.h"
#include "common/components/MeshComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/helpers/MeshUtils.h"
#include "common/worldcomponents/DebugManager.h"
#include "common/worldcomponents/InputManager.h"
#include "engine/core/ForgeEngine.h"
#include "engine/shader/ShaderUtils.h"

int main()
{
    Torch::Torch instance("Torch", 1920, 1080);
    instance.HandleProcess();
}

namespace Torch
{
    Torch::Torch(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Torch::OnInit() /*override*/
    {
        Mother::OnInit();

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
        m_Light->RegisterComponent(new LightComponent(30.f, 10.f, lightColor));
        m_Light->GetTransform().Translate(VECTOR3_UP * 2.f + VECTOR3_SIDE * 2.f);

        Entity* cube1 = world.RegisterEntity("MarbleCube");
        cube1->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, "assets\\materials\\marble.mat"), "assets\\shaders\\lit"));
        cube1->GetTransform().Translate(VECTOR3_UP * 1.7f);

        m_Cube = world.RegisterEntity("RubyCube");
        m_Cube->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, "assets\\materials\\ruby.mat"), "assets\\shaders\\lit"));
        m_Cube->GetTransform().Translate(Vector3(4.f, 0.5f, 4.f));

        //using Vector3f = Vector<3, float>;
        //Vector3f test(std::initializer_list<float>{1.f, 2.f, 3.f});

        Vector3f test(1.f, 2.f, 3.f);
        Vector3f test2(3.f, 5.f, 7.f);
        //float dot = test.Dot(test2);
        Vector3f cross = test.Cross(test2);
        bool yolo = true;
    }

    void Torch::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_BLACK);
        Vector3 position = m_Light->GetPosition();
        m_Light->GetTransform().SetPosition(Vector3(position.x, 2.f + (sin(static_cast<float>(glfwGetTime()) * 2.0f)), position.z));
        m_Cube->GetTransform().Rotate(VECTOR3_UP * 90.f * dT);
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