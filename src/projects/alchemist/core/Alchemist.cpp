#include "alchemist.h"

#include "projects/alchemist/components/LandscapeComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/DebugManager.h"
#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"
#include "system/misc/Color.h"
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