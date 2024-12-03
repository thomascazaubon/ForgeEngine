#pragma once

#include "glm/vec3.hpp"
#include <cmath>
#include <stdarg.h>
#include <initializer_list>
#include <type_traits>
#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	#define VECTOR3_SIDE Vector3(1.f, 0.f, 0.f)
	#define VECTOR3_UP Vector3(0.f, 1.f, 0.f)
	#define VECTOR3_FORWARD Vector3(0.f, 0.f, 1.f)

	#define VECTOR3_UNIT Vector3(1.f, 1.f, 1.f)
	#define VECTOR3_NULL Vector3(0.f, 0.f, 0.f)

    using Vector3 = glm::vec3;

	namespace ForgeMaths
	{
		Vector3 Flatten(const Vector3& v);
		Vector3 FlattenAndNormalize(const Vector3& v);
		Vector3 Cross(const Vector3& v1, const Vector3& v2);
		Vector3 Normalize(const Vector3& v);
		float Dot(const Vector3& v1, const Vector3& v2);
		float Distance(const Vector3& v1, const Vector3& v2);
	}
    
    /*
    template <unsigned int N, typename T>
    class Vector : public glm::vec<N, T, glm::defaultp>
    {
        public:
            using Mother = glm::vec<N, T, glm::defaultp>;
            using Mother::vec;

            T Dot(const Mother& other) const
            {
                return glm::dot(*this, other);
            }

            T Length() const
            {
                return this.length();
            }

            Vector<N, T> Cross(const Mother& other)
            {
                return *this;//glm::cross(*this, other);
            }

            T Distance(const Vector<N, T>& other)
            {
                return (other - *this).Length();
            }

            Vector<N, T> GetNormalized()
            {
                return glm::normalize(*this);
            }

            void Normalize()
            {
                *this = glm::normalize(*this);
            }
    };

    using Vector3f = Vector<3, float>;
    using Vector3d = Vector<3, double>;
    */
}