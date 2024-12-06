#include "Matrix4.h"

#include "Vector3.h"
#include "Vector4.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		void Translate(Matrix4& matrix, const Vector3& direction)
		{
			matrix = glm::translate(matrix, Vector3(direction));
		}

		void Rotate(Matrix4& matrix, float angle, const Vector3& axis)
		{
			matrix = glm::rotate(matrix, glm::radians(angle), Vector3(axis));
		}

		void Rotate(Matrix4& matrix, const Vector3& eulerAngles)
		{
			Rotate(matrix, eulerAngles.x, VECTOR3_SIDE);
			Rotate(matrix, eulerAngles.y, VECTOR3_UP);
			Rotate(matrix, eulerAngles.z, VECTOR3_FORWARD);
		}

		void Scale(Matrix4& matrix, const Vector3& scale)
		{
			matrix = glm::scale(matrix, scale);
		}

        void Scale(Matrix4& matrix, float scale)
        {
            matrix = glm::scale(matrix, Vector3(scale));
        }

		void Decompose(const Matrix4& matrix, Vector3& position, Vector3& rotation, Vector3& scale)
		{
			glm::quat quaternion;
			Vector3 skew;
			Vector4 perspective;

			glm::decompose(matrix, scale, quaternion, position, skew, perspective);

			rotation = glm::eulerAngles(quaternion);
		}

		void LookAt(Matrix4& matrix, const Vector3& from, const Vector3& to, const Vector3& upDirection)
		{
			matrix = glm::lookAt(from, to, upDirection);
		}
	}
}