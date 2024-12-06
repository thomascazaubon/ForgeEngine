#pragma once

#include "Vector3.h"

#include "glm/mat4x4.hpp"

namespace ForgeEngine
{
	typedef glm::mat4x4 Matrix4;

	namespace ForgeMaths
	{
		void Translate(Matrix4& matrix, const Vector3& direction);
		void Rotate(Matrix4& matrix, float angle, const Vector3& axis);
		void Rotate(Matrix4& matrix, const Vector3& eulerAngles);
		void Scale(Matrix4& matrix, const Vector3& scale);
		void Scale(Matrix4& matrix, float scale);

		void Decompose(const Matrix4& matrix, Vector3& position, Vector3& rotation, Vector3& scale);
		void LookAt(Matrix4& matrix, const Vector3& from, const Vector3& to, const Vector3& upDirection);
	}
}