#include "Mesh.h"

#include "common/worldcomponents/MaterialLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/core/World.h"
#include "engine/shader/Material.h"

#include <iostream>
#include <format>

namespace ForgeEngine
{
    Mesh::Mesh(const std::vector<Vector3>& vertices,
        const std::vector<unsigned int>& triangleIndices,
        const std::vector<Vector2>& textureCoordinates,
        const char* materialPath /*= nullptr*/)
        : m_Vertices(vertices)
    {
        if (materialPath == nullptr)
        {
            m_Material = std::shared_ptr<Material>(*(GameHandler::Get().GetWorld().GetComponentByType<MaterialLoader>()->GetDefault()));
        }
        else
        {
            m_Material = std::shared_ptr<Material>(*(GameHandler::Get().GetWorld().GetComponentByType<MaterialLoader>()->GetOrLoadResource(materialPath)));
        }

        for (unsigned int i = 0; i < triangleIndices.size(); i += 3)
        {
            unsigned int indices[3];
            Vector2 texture[3];

            for (unsigned int j = 0; j < 3; j++)
            {
                indices[j] = triangleIndices[i + j];
                texture[j] = textureCoordinates[i + j];
            }

            m_Triangles.push_back(Triangle(*this, indices, texture));
        }
    }

    Mesh::Triangle::Triangle(const Mesh& owningMesh, const unsigned int indices[3], const Vector2 textureCoordinates[3])
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            Vertex vertex;
            vertex.m_Index = indices[i];
            vertex.m_TextureCoordinates = textureCoordinates[i];
            m_Vertices[i] = vertex;
        }

        ComputeNormal(owningMesh);
    }

    void Mesh::Triangle::ComputeNormal(const Mesh& owningMesh)
    {
        const std::vector<Vector3>& verticesCoordinates = owningMesh.GetVertices();

        const Vector3& v1 = verticesCoordinates[m_Vertices[0].m_Index];
        const Vector3& v2 = verticesCoordinates[m_Vertices[1].m_Index];
        const Vector3& v3 = verticesCoordinates[m_Vertices[2].m_Index];

        const Vector3 directionToMeshOrigin = ForgeMaths::Normalize(-(v1 + v2 + v3) / 3.f);
        m_Normal = ForgeMaths::Normalize(ForgeMaths::Cross(v2 - v1, v3 - v1));

        //Flip inward facing normals
        if (directionToMeshOrigin.y == 0.f || ForgeMaths::Dot(m_Normal, directionToMeshOrigin) > 0.f)
        {
            m_Normal = -m_Normal;
        }
    }

    std::vector<float> Mesh::Triangle::ToGLData(const Mesh& owningMesh) const
    {
        std::vector<float> data;
        
        const std::vector<Vector3>& verticesCoordinates = owningMesh.GetVertices();

        for (unsigned int i = 0; i < 3; i++)
        {
            const Vector3& vertexCoordinates = verticesCoordinates[m_Vertices[i].m_Index];
            data.push_back(vertexCoordinates.x);
            data.push_back(vertexCoordinates.y);
            data.push_back(vertexCoordinates.z);
            data.push_back(m_Normal.x);
            data.push_back(m_Normal.y);
            data.push_back(m_Normal.z);
            data.push_back(m_Vertices[i].m_TextureCoordinates.x);
            data.push_back(m_Vertices[i].m_TextureCoordinates.y);
        }

        return data;
    }

    std::vector<float> Mesh::MakeGLData() const
    {
        std::vector<float> data;

        for (unsigned int i = 0; i < GetTrianglesCount(); i++)
        {
            const std::vector<float> triangleData = m_Triangles[i].ToGLData(*this);
            for (unsigned int j = 0; j < triangleData.size(); j++)
            {
                data.push_back(triangleData[j]);
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
            unsigned int startIndex = i * 3;
            for (unsigned int j = 0; j < 3; j++)
            {
                indices.push_back(triangle.m_Vertices[j].m_Index);
            }
        }

        return indices;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Mesh::OnDrawDebug() const
    {
        if (ImGui::CollapsingHeader("Vertices"))
        {
            ImGui::Indent();
            {
                for (const Vector3& vertex : m_Vertices)
                {
                    ImGui::Text("(%.2f, %.2f, %.2f)", vertex.x, vertex.y, vertex.z);
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
                const unsigned int dataSize = Triangle::Vertex::GetGLDataSize();
                const std::vector<float> glData = MakeGLData();
                unsigned int numVertices = 0;

                for (unsigned int i = 0; i < glData.size(); i++)
                {
                    //New vertex
                    if (i > 0 && i % dataSize == 0)
                    {
                        numVertices++;
                        stringData += numVertices > 0 && numVertices % 3 == 0 ? "\n\n" : "\n";
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
        ImGui::Text("%i - %i - %i", m_Vertices[0].m_Index, m_Vertices[1].m_Index, m_Vertices[2].m_Index);
    }
#endif //FORGE_DEBUG_ENABLED
}