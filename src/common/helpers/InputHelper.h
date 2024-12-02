#pragma once

#include "system/input/InputAction.h"
#include "system/math/Vector2.h"

namespace ForgeEngine
{
	enum class EInputAction;

	namespace InputHelper
	{
		bool IsInputActive(EInputAction type);
		Vector2 GetMouseVelocity();
		Vector2 GetMousePosition();
	}
}