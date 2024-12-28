#include "DebugElements.h"

#include "engine/components/CameraComponent.h"
#include "engine/core/Entity.h"
#include "engine/render/OpenGL.h"
#include "engine/render/Shader.h"

namespace ForgeEngine
{
    DebugElement::DebugElement(const Color& color, unsigned int durationMs)
        : m_Color(color)
    {
        m_Timer.Start(durationMs);
    }

    void DebugElement::InitializeRender(const float verticesData[], unsigned int dataSize)
    {
        glGenBuffers(1, &m_VertexBufferObject);
        glGenVertexArrays(1, &m_VertexArrayObject);

        //Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

        //1. Bind Vertex Array Object
        glBindVertexArray(m_VertexArrayObject);

        //2. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
        const GLintptr meshDataSize = dataSize * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, meshDataSize, verticesData, GL_STATIC_DRAW);

        //3. Then set our vertex attributes pointers
        //1st argument corresponds to the vertex attribute location (comes from vertexShaderSource)
        //2nd argument corresponds to the number of floats in the attribute (used in the vertex shader)
        //5th argument corresponds to the size of the attribute in bytes
        //Should be done for each attribute of the vertexShader, eg each in variable
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Unbinding, this is optionnal
        //Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        //VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    void DebugElement::Draw(Shader& shader) const
    {
        glDisable(GL_DEPTH_TEST);

        shader.Use();

        if (const CameraComponent* camera = CameraComponent::GetActiveCamera())
        {
            shader.SetMatrix4(DEFAULT_PROJECTION_NAME, camera->GetProjection());
            shader.SetMatrix4(DEFAULT_VIEW_NAME, camera->GetView());
        }

        shader.SetColor(DEFAULT_RENDER_COLOR_NAME, m_Color);

        glBindVertexArray(m_VertexArrayObject);
        glDrawArrays(GetDrawMode(), 0, GetVerticesCount() * 3);
    }

    DebugLine::DebugLine(const Color& color, const Vector3& lineStart, const Vector3& lineEnd, unsigned int durationMS)
        : Mother(color, durationMS)
    {
        m_CenterPosition = lineStart;
        float verticesData[6]{ lineStart.x, lineStart.y, lineStart.z, lineEnd.x, lineEnd.y, lineEnd.z };
        InitializeRender(verticesData, 6);
    }

    unsigned int DebugLine::GetDrawMode() const
    {
        return GL_LINES;
    }

    DebugSphere::DebugSphere(const Color& color, const Vector3& centre, float radius, unsigned int durationMS)
        : Mother(color, durationMS)
    {
    }
}
