#pragma once

#include "system/math/Vector3.h"

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		Vector3 ComputeCameraSight(float yaw, float pitch);
		
		template <typename T>
		T Clamp(T value, T minValue, T maxValue)
		{
			T retValue = value;
			if (retValue < minValue)
			{
				retValue = minValue;
			}
			else if (retValue > maxValue)
			{
				retValue = maxValue;
			}
			return retValue;
		}

		template <typename T1, typename T2, typename T3>
		bool IsBetween(T1 value, T2 inf, T3 sup)
		{
			return (value >= inf && value <= sup);
		}

		template <typename T1, typename T2, typename T3>
		bool IsBetweenExclusive(T1 value, T2 inf, T3 sup)
		{
			return (value > inf && value < sup);
		}
	}
}

