#pragma once

#include "DebugElements.h"

#include "engine/math/Vector3.h"

#include <vector>

namespace ForgeEngine
{
    class Color;

    class DebugDrawer
    {
        public:
            DebugDrawer(const std::shared_ptr<Shader>& drawShader);

            void CreateLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int duration);
            void Update();

        private:
            std::shared_ptr<Shader> m_DrawShader;
            std::vector<DebugElement*> m_ActiveElements;
    };
}