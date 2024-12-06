#include "MathUtils.h"

#include <glm/glm.hpp>

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		Vector3 ComputeCameraSight(float yaw, float pitch)
		{
			return Vector3
			{
				cos(glm::radians(yaw))* cos(glm::radians(pitch)),
				sin(glm::radians(pitch)),
				sin(glm::radians(yaw))* cos(glm::radians(pitch))
			};
		}
	}
}