#include "common/helpers/InputHelper.h"

#include "common/worldcomponents/InputManager.h"
#include "engine/core/GameHandler.h"
#include "engine/core/World.h"

namespace ForgeEngine
{
	namespace InputHelper
	{
		bool IsInputActive(EInputAction type)
		{
			if (InputManager* inputManager = GameHandler::Get().GetWorld().GetComponentByType<InputManager>())
			{
				return inputManager->IsInputActive(type);
			}
			return false;
		}

		Vector2 GetMouseVelocity()
		{
			if (InputManager* inputManager = GameHandler::Get().GetWorld().GetComponentByType<InputManager>())
			{
				return inputManager->GetMouseVelocity();
			}
			return VECTOR2_NULL;
		}

		Vector2 GetMousePosition()
		{
			if (InputManager* inputManager = GameHandler::Get().GetWorld().GetComponentByType<InputManager>())
			{
				return inputManager->GetMousePosition();
			}
			return VECTOR2_NULL;
		}
	}
}