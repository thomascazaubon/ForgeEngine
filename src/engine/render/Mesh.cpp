#include "Mesh.h"

#include "engine/assetloaders/MaterialLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/core/World.h"
#include "engine/debug/Assert.h"
#include "engine/render/Material.h"

#include <iostream>
#include <format>

namespace ForgeEngine
{
    Mesh::Mesh(const std::vector<Vector3>& vertices,
        const std::vector<unsigned int>& triangleIndices,
        const std::vector<Vector2>& textureCoordinates,
        const char* materialPath /*= nullptr*/)
    {
        if (materialPath == nullptr)
        {
            m_Material = std::shared_ptr<Material>(*(GameHandler::Get().GetWorld().GetComponentByType<MaterialLoader>()->GetDefault()));
        }
        else
        {
            m_Material = std::shared_ptr<Material>(*(GameHandler::Get().GetWorld().GetComponentByType<MaterialLoader>()->GetOrLoadResource(materialPath)));
        }

        BuildMesh(vertices, triangleIndices, textureCoordinates);
    }

    Mesh::Mesh(const std::vector<Vector3>& vertices,
        const std::vector<unsigned int>& triangleIndices,
        const std::vector<Vector2>& textureCoordinates,
        const std::shared_ptr<Material>& material)
        : m_Material(material)
    {
        BuildMesh(vertices, triangleIndices, textureCoordinates);
    }

    void Mesh::BuildMesh(const std::vector<Vector3>& vertices,
        const std::vector<unsigned int>& triangleIndices,
        const std::vector<Vector2>& textureCoordinates)
    {
        ASSERT(triangleIndices.size() % 3 == 0, "Invalid triangles count");

        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            Vertex vertex;
            vertex.m_Position = vertices[i];
            vertex.m_TextureCoordinates = textureCoordinates[i];
            m_Vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < triangleIndices.size(); i += 3)
        {
            unsigned int indices[3]{ triangleIndices[i], triangleIndices[i + 1], triangleIndices[i + 2] };
            Vector2 coordinates[3]{ textureCoordinates[i], textureCoordinates[i + 1], textureCoordinates[i + 2] };
            Triangle triangle(*this, indices, coordinates);
            for (unsigned int j = 0; j < 3; j++)
            {
                m_Vertices[indices[j]].m_Normal = triangle.m_Normal;
            }
            m_Triangles.push_back(triangle);
        }
    }

    std::vector<float> Mesh::Vertex::ToGLData() const
    {
        return std::vector<float>{
            m_Position.x,
            m_Position.y,
            m_Position.z,
            m_Normal.x,
            m_Normal.y,
            m_Normal.z,
            m_TextureCoordinates.x,
            m_TextureCoordinates.y
        };
    }

    std::vector<float> Mesh::MakeGLData(DrawMode drawMode) const
    {
        std::vector<float> data;

        if (drawMode == DrawMode::Elements)
        {
            for (unsigned int i = 0; i < m_Vertices.size(); i++)
            {
                const std::vector<float> vertexData = m_Vertices[i].ToGLData();
                for (unsigned int j = 0; j < vertexData.size(); j++)
                {
                    data.push_back(vertexData[j]);
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < m_Triangles.size(); i++)
            {
                const Triangle& triangle = m_Triangles[i];
                for (unsigned int j = 0; j < 3; j++)
                {
                    Vertex vertex = m_Vertices[triangle.m_Indices[j]];
                    vertex.m_TextureCoordinates = triangle.m_TextureCoordinates[j];
                    vertex.m_Normal = triangle.m_Normal;
                    const std::vector<float> vertexData = vertex.ToGLData();

                    for (unsigned int k = 0; k < vertexData.size(); k++)
                    {
                        data.push_back(vertexData[k]);
                    }
                }
            }
        }

        return data;
    }

    std::vector<unsigned int> Mesh::GetTrianglesIndices() const
    {
        std::vector<unsigned int> indices;
        
        for (unsigned int i = 0; i < GetTrianglesCount(); i++)
        {
            const Triangle& triangle = m_Triangles[i];
            for (unsigned int j = 0; j < 3; j++)
            {
                indices.push_back(triangle.m_Indices[j]);
            }
        }

        return indices;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Mesh::OnDrawDebug(DrawMode drawMode) const
    {
        if (ImGui::CollapsingHeader("Vertices"))
        {
            ImGui::Indent();
            {
                for (const Vertex& vertex : m_Vertices)
                {
                    ImGui::Text("(%.2f, %.2f, %.2f)", vertex.m_Position.x, vertex.m_Position.y, vertex.m_Position.z);
                }
            }
            ImGui::Unindent();
        }
        if (ImGui::CollapsingHeader("Triangles"))
        {
            ImGui::Indent();
            {
                for (const Triangle& triangle : m_Triangles)
                {
                    triangle.OnDrawDebug();
                }
            }
            ImGui::Unindent();
        }
        if (ImGui::CollapsingHeader("GL Data"))
        {
            ImGui::Indent();
            {
                std::string stringData = "";
                const unsigned int dataSize = Vertex::GetGLDataSize();
                const std::vector<float> glData = MakeGLData(drawMode);
                unsigned int numVertices = 0;

                for (unsigned int i = 0; i < glData.size(); i++)
                {
                    //New vertex
                    if (i > 0 && i % dataSize == 0)
                    {
                        stringData += "\n";
                    }
                    
                    stringData += std::format("[{:.2f}]", glData[i]);
                }
                ImGui::Text("%s", stringData.c_str());
            }
            ImGui::Unindent();
        }
    }

    void Mesh::Triangle::OnDrawDebug() const
    {
        ImGui::Text("%i - %i - %i", m_Indices[0], m_Indices[1], m_Indices[2]);
    }
#endif //FORGE_DEBUG_ENABLED

    Mesh::Triangle::Triangle(const Mesh& owningMesh, const unsigned int indices[3], const Vector2 textureCoordinates[3])
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            m_Indices[i] = indices[i];
            m_TextureCoordinates[i] = textureCoordinates[i];
        }

        ComputeNormal(owningMesh);
    }

    void Mesh::Triangle::ComputeNormal(const Mesh& owningMesh)
    {
        const std::vector<Vertex>& verticesCoordinates = owningMesh.GetVertices();

        const Vector3& v1 = verticesCoordinates[m_Indices[0]].m_Position;
        const Vector3& v2 = verticesCoordinates[m_Indices[1]].m_Position;
        const Vector3& v3 = verticesCoordinates[m_Indices[2]].m_Position;

        const Vector3 directionToMeshOrigin = ForgeMaths::Normalize(-(v1 + v2 + v3) / 3.f);
        m_Normal = ForgeMaths::Normalize(ForgeMaths::Cross(v2 - v1, v3 - v1));

        //Flip inward facing normals
        if (directionToMeshOrigin.y == 0.f || ForgeMaths::Dot(m_Normal, directionToMeshOrigin) > 0.f)
        {
            m_Normal = -m_Normal;
        }
    }
}