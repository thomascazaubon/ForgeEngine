#include "MeshUtils.h"

#include "engine/assetloaders/MaterialLoader.h"
#include "engine/core/GameHandler.h"
#include "engine/math/Vector2.h"
#include "engine/math/Vector3.h"
#include "engine/render/Material.h"
#include "engine/render/Texture.h"

namespace ForgeEngine
{
    namespace MeshUtils
    {
        /********CUBE********/

        std::vector<Vector3> GetCubeVerticesCoordinates(float scale = 1.f)
        {
            return std::vector<Vector3>
            {
                /*
                                   .H------G
                                 .' |    .'|
                                E---+--F'  |
                                |   |  |   |
                                |  .D--+---C
                                |.'    | .'
                                A------B'
                */

                Vector3(-scale / 2.f, -scale / 2.f, -scale / 2.f), //0 - A
                Vector3(scale / 2.f, -scale / 2.f, -scale / 2.f),  //1 - B
                Vector3(scale / 2.f, -scale / 2.f, scale / 2.f),   //2 - C
                Vector3(-scale / 2.f, -scale / 2.f, scale / 2.f),  //3 - D
                Vector3(-scale / 2.f, scale / 2.f, -scale / 2.f),  //4 - E
                Vector3(scale / 2.f, scale / 2.f, -scale / 2.f),   //5 - F
                Vector3(scale / 2.f, scale / 2.f, scale / 2.f),    //6 - G
                Vector3(-scale / 2.f, scale / 2.f, scale / 2.f)    //7 - H
            };
        }

        std::vector<unsigned int> GetCubeVerticesIndexes()
        {
            return  std::vector<unsigned int>
            {
                /******************FRONT*******************/
                0, 1, 4, //A,B,E
                4, 5, 1, //E,F,B
                /******************RIGHT*******************/
                1, 2, 5, //B,C,F
                5, 6, 2, //F,G,C
                /******************BACK********************/
                2, 3, 6, //C,D,G
                6, 7, 3, //G,H,D
                /******************LEFT********************/
                3, 0, 7, //D,A,H
                7, 4, 0, //H,E,A
                /******************TOP*********************/
                4, 5, 7, //E,F,H
                7, 6, 5, //H,G,F
                /******************BOTTOM******************/
                0, 1, 3, //A,B,D
                3, 2, 1  //D,C,B
            };
        }

        std::vector<Vector2> GetCubeTextureCoordinates(float scale)
        {
            return std::vector<Vector2>
            {
                /******************FRONT*******************/
                Vector2(0.f, 0.f),   //A -> ABE
                Vector2(scale, 0.f), //B -> ABE
                Vector2(0.f, scale), //E -> ABE

                Vector2(0.f, scale), //E -> EFB
                Vector2(scale, 1.f), //F -> EFB
                Vector2(scale, 0.f), //B -> EFB
                /******************RIGHT*******************/
                    Vector2(0.f, 0.f),   //A -> ABE
                    Vector2(scale, 0.f), //B -> ABE
                    Vector2(0.f, scale), //E -> ABE

                    Vector2(0.f, scale), //E -> EFB
                    Vector2(scale, 1.f), //F -> EFB
                    Vector2(scale, 0.f), //B -> EFB
                /******************BACK********************/
                    Vector2(0.f, 0.f),   //A -> ABE
                    Vector2(scale, 0.f), //B -> ABE
                    Vector2(0.f, scale), //E -> ABE

                    Vector2(0.f, scale), //E -> EFB
                    Vector2(scale, 1.f), //F -> EFB
                    Vector2(scale, 0.f), //B -> EFB
                /******************LEFT********************/
                    Vector2(0.f, 0.f),   //A -> ABE
                    Vector2(scale, 0.f), //B -> ABE
                    Vector2(0.f, scale), //E -> ABE

                    Vector2(0.f, scale), //E -> EFB
                    Vector2(scale, 1.f), //F -> EFB
                    Vector2(scale, 0.f), //B -> EFB
                /******************TOP*********************/
                    Vector2(0.f, 0.f),   //A -> ABE
                    Vector2(scale, 0.f), //B -> ABE
                    Vector2(0.f, scale), //E -> ABE

                    Vector2(0.f, scale), //E -> EFB
                    Vector2(scale, 1.f), //F -> EFB
                    Vector2(scale, 0.f), //B -> EFB
                /******************BOTTOM******************/
                    Vector2(0.f, 0.f),   //A -> ABE
                    Vector2(scale, 0.f), //B -> ABE
                    Vector2(0.f, scale), //E -> ABE

                    Vector2(0.f, scale), //E -> EFB
                    Vector2(scale, 1.f), //F -> EFB
                    Vector2(scale, 0.f), //B -> EFB
            };
        }

        /********PLANE********/

        std::vector<Vector3> GetPlaneVerticesCoordinates(float length = 1.f, float width = 1.f, bool flat = true)
        {
            return std::vector<Vector3>
            {
                /*
                                    .D------C
                                  .'      .'
                                A------B'
                */

                Vector3(-width / 2.f, flat ? 0.f : -length / 2.f, flat ? -length / 2.f : 0.f), //0 - A
                Vector3(width / 2.f, flat ? 0.f : -length / 2.f, flat ? -length / 2.f : 0.f),  //1 - B
                Vector3(width / 2.f, flat ? 0.f : length / 2.f, flat ? length / 2.f : 0.f),  //2 - C
                Vector3(-width / 2.f, flat ? 0.f : length / 2.f, flat ? length / 2.f : 0.f)  //3 - D
            };
        }

        std::vector<unsigned int> GetPlaneVerticesIndexes()
        {
            return  std::vector<unsigned int>
            {
                0, 1, 3, //ABD
                1, 2, 3  //BCD
            };
        }

        std::vector<Vector2> GetPlaneTextureCoordinates(float scale = 1.f)
        {
            return std::vector<Vector2>
            {
                Vector2(0.f, 0.f),     //A -> ABD
                Vector2(scale, 0.f),   //B -> ABD
                Vector2(0.f, scale),   //D -> ABD

                Vector2(scale, 0.f),   //B -> BCD
                Vector2(scale, scale), //C -> BCD
                Vector2(0.f, scale),   //D -> BCD
            };
        }

        /********TRIANGLE********/

        std::vector<Vector3> GetTriangleVerticesCoordinates(float scale/* = 1.f*/)
        {
            return std::vector<Vector3>
            {
                /*
                                    .D------C
                                  .'      .'
                                A------B'
                */

                Vector3(-scale / 2.f, 0.f, -scale / 2.f), //A
                Vector3( scale / 2.f, 0.f, -scale / 2.f), //B
                Vector3( 0.f, 0.f, scale / 2.f)  //C
            };
        }

        std::vector<unsigned int> GetTriangleVerticesIndexes()
        {
            return  std::vector<unsigned int>
            {
                0, 1, 2 //ABC
            };
        }

        std::vector<Vector2> GetTriangleTextureCoordinates(float scale/* = 1.f*/)
        {
            return std::vector<Vector2>
            {
                Vector2(0.f, 0.f),           //A -> ABC
                Vector2(scale, 0.f),         //B -> ABC
                Vector2(scale/2.f, scale),   //C -> ABC
            };
        }

        /********SPHERE********/

        std::vector<Vector3> GetSphereVerticesCoordinates(float scale = 1.f)
        {
            return std::vector<Vector3>();
        }

        std::vector<unsigned int> GetSphereVerticesIndexes()
        {
            return std::vector<unsigned int>();
        }

        std::vector<Vector2> GetSphereTextureCoordinates(float scale = 1.f)
        {
            return std::vector<Vector2>();
        }

        /********HEADER FUNCTIONS********/

        Mesh MakeCube(float scale /*= 1.f*/, const char* materialPath /* =nullptr*/)
        {
            return Mesh(GetCubeVerticesCoordinates(scale), GetCubeVerticesIndexes(), GetCubeTextureCoordinates(scale), materialPath);
        }

        Mesh MakePlane(float scale /*= 1.f*/, const char* materialPath /* =nullptr*/)
        {
            return Mesh(GetPlaneVerticesCoordinates(scale, scale), GetPlaneVerticesIndexes(), GetPlaneTextureCoordinates(scale), materialPath);
        }

        Mesh MakeSprite(const char* materialPath, float height /*= 1.f*/)
        {
            const std::shared_ptr<Material>* material = GameHandler::Get().GetWorld().GetComponentByType<MaterialLoader>()->GetOrLoadResource(materialPath);
            float heightWidthRatio = 1.f;

            if (const Texture* texture = material->get()->GetTexture())
            {
                heightWidthRatio = texture->GetWidth() / static_cast<float>(texture->GetHeight());
            }

            return Mesh(GetPlaneVerticesCoordinates(height, height * heightWidthRatio, false), GetPlaneVerticesIndexes(), GetPlaneTextureCoordinates(1.f), *material);
        }

        Mesh MakeTriangle(float scale /*= 1.f*/, const char* materialPath /* =nullptr*/)
        {
            return Mesh(GetTriangleVerticesCoordinates(scale), GetTriangleVerticesIndexes(), GetTriangleTextureCoordinates(scale), materialPath);
        }

        Mesh MakeSphere(float scale /*= 1.f*/, const char* materialPath /* =nullptr*/)
        {
            return Mesh(GetSphereVerticesCoordinates(scale), GetSphereVerticesIndexes(), GetSphereTextureCoordinates(scale), materialPath);
        }
    }
}