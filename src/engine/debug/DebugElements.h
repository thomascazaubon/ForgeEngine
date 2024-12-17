#pragma once

#include "engine/render/Color.h"
#include "engine/math/Vector3.h"
#include "engine/time/Timer.h"

namespace ForgeEngine
{
    class Shader;

    class DebugElement
    {
        public:
            DebugElement(const Color& color, unsigned int durationMs);

            void Draw(Shader& shader) const;
            bool HasExpired() const { return m_Timer.IsElapsed(); }

        protected:
            void InitializeRender(const float verticesData[], unsigned int dataSize);

            virtual unsigned int GetVerticesCount() const = 0;
            virtual unsigned int GetDrawMode() const = 0;

            Timer m_Timer;
            Color m_Color;
            Vector3 m_CenterPosition;
            unsigned int m_VertexArrayObject{};
            unsigned int m_VertexBufferObject{};
    };

    class DebugLine : public DebugElement
    {
        using Mother = DebugElement;
        public:
            DebugLine(const Color& color, const Vector3& lineStart, const Vector3& lineEnd, unsigned int durationMS);

        protected:
            unsigned int GetVerticesCount() const override { return 2; }
            unsigned int GetDrawMode() const override;
    };

    class DebugSphere : public DebugElement
    {
        using Mother = DebugElement;
    public:
        DebugSphere(const Color& color, const Vector3& centre, float radius, unsigned int durationMS);
    };
}
