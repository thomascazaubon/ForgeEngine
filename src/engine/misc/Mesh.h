#pragma once

#include "system/math/Vector2.h"
#include "system/math/Vector3.h"
#include "system/misc/Color.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
    class Material;
    class Texture;

    //TODO: TEXTURE MEMORY LEAK
    //TODO: MAKE NON COPYABLE
    class Mesh
    {
    public:
        Mesh() {}
        Mesh(const std::vector<Vector3>& vertices, 
            const std::vector<unsigned int>& triangleIndices, 
            const std::vector<Vector2>& textureCoordinates,
            const char* materialPath = nullptr);

        const std::vector<Vector3>& GetVertices() const { return m_Vertices; }
        unsigned int GetVerticesCount() const { return m_Vertices.size(); }
        unsigned int GetTrianglesCount() const { return m_Triangles.size(); }
        const Material* GetMaterial() const { return m_Material.get(); }

        //data format [vx, xy, vz, nx, ny, nz, tx, ty] * GetTrianglesCount() * 3
        //v = vertex coordinates
        //n = normal coordinates
        //t = texture coordinates
        //array size = outNumVertices * outVertexDataSize
        std::vector<float> MakeGLData() const;
        std::vector<unsigned int> GetTrianglesIndices() const;

    private:
        struct Triangle
        {
            struct Vertex
            {
                unsigned int m_Index;
                Vector2 m_TextureCoordinates;

                static unsigned int GetGLDataSize() { return 8; }
            };

            Triangle(const Mesh& owningMesh, const unsigned int indices[3], const Vector2 textureCoordinates[3]);

            Vertex m_Vertices[3];
            Vector3 m_Normal;

            void ComputeNormal(const Mesh& owningMesh);

            std::vector<float> ToGLData(const Mesh& owningMesh) const;
            static unsigned int GetGLDataSize() { return Vertex::GetGLDataSize() * 3; }
        };

        std::vector<Vector3> m_Vertices{};
        std::vector<Triangle> m_Triangles{};

        std::shared_ptr<Material> m_Material{ nullptr };
    };
}