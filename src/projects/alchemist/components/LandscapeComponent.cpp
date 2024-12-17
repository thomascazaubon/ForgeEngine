#include "LandscapeComponent.h"

#include "engine/components/MeshComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/debug/ImGUICore.h"
#include "engine/input/InputHelper.h"
#include "engine/math/MathUtils.h"
#include "engine/render/Texture.h"

#include <cstdlib>
#include <vector>

namespace Alchemist
{
    bool LandscapeComponent::OnPreInit() /*override*/
    {
        std::vector<float> vertices
        {
            ALCHEMIST_WINDOW_WIDTH, ALCHEMIST_WINDOW_HEIGHT, 0.f, 1.f, 1.f, // top right
            ALCHEMIST_WINDOW_WIDTH, 0.f, 0.f, 1.f, 0.f, // bottom right
            0.f, 0.f, 0.f, 0.f, 0.f, // bottom left
            0.f, ALCHEMIST_WINDOW_HEIGHT, 0.f, 0.f, 1.f  // top left 
        };

        std::vector<unsigned int> indices
        {
            0, 1, 3,
            1, 2, 3
        };

        //TODO: FIX THIS
        //GetOwner()->RegisterComponent(new MeshComponent(vertices, indices, GetOwner()->GetWorld().GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Textured)));

        return true;
    }

    void LandscapeComponent::OnPreUpdate(float dT) /*override*/
    {
        Mother::OnPreUpdate(dT);

        Vector2 mousePosition = GetMousePosition();
        unsigned int pixelX = (unsigned int)mousePosition.x;
        unsigned int pixelY = ALCHEMIST_LANDSCAPE_HEIGHT - (unsigned int)mousePosition.y;

        if (ForgeMaths::IsBetween(pixelY, 0, ALCHEMIST_LANDSCAPE_HEIGHT - 1) && 
            ForgeMaths::IsBetween(pixelX, 0, ALCHEMIST_LANDSCAPE_WIDTH - 1) &&
            m_ParticleContainer[pixelY][pixelX].m_Type == EParticleType::Air)
        {
            if (InputHelper::IsInputActive(EInputAction::LeftClick))
            {
                SpawnParticle(EParticleType::Sand, pixelX, pixelY);
            }
            else if (InputHelper::IsInputActive(EInputAction::RightClick))
            {
                SpawnParticle(EParticleType::Water, pixelX, pixelY);
            }
        }

        UpdateParticles();

        DrawTexture();

        if (MeshComponent* mesh = GetOwner()->GetComponentByType<MeshComponent>())
        {
            //TODO: FIX THIS
            //mesh->GetMesh().SetTexture(m_Texture.get());
        }
    }

    void LandscapeComponent::OnDrawDebug(float dT) const  /*override*/ 
    {
        Vector2 mousePosition = GetMousePosition();
        float heightConversionRatio = GameHandler::Get().GetWindowHeight() / static_cast<float>(ALCHEMIST_LANDSCAPE_HEIGHT);
        float widthConversionRatio = GameHandler::Get().GetWindowWidth() / static_cast<float>(ALCHEMIST_LANDSCAPE_WIDTH);

        ImGui::Text("Grid Size: %d x %d", ALCHEMIST_LANDSCAPE_WIDTH, ALCHEMIST_LANDSCAPE_HEIGHT);
        ImGui::Text("Grid Mouse Position {%d,%d}", static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y));
        ImGui::Text("Conversion Ratio {%f,%f}", heightConversionRatio, widthConversionRatio);
    }

    Vector2 LandscapeComponent::GetMousePosition() const
    {
        float heightConversionRatio = GameHandler::Get().GetWindowHeight() / (float)ALCHEMIST_LANDSCAPE_HEIGHT;
        float widthConversionRatio = GameHandler::Get().GetWindowWidth() / (float)ALCHEMIST_LANDSCAPE_WIDTH;
        Vector2 mousePosition = InputHelper::GetMousePosition();
        return Vector2{ mousePosition.x / widthConversionRatio, mousePosition.y / heightConversionRatio };
    }

    void LandscapeComponent::UpdateParticles()
    {
        for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
        {
            for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
            {
                if (!m_ParticleContainer[y][x].m_HasBeenUpdated)
                {
                    m_ParticleContainer[y][x].m_HasBeenUpdated = true;
                    EParticleType particleBeneath = GetSurroundingParticleType(EDirection::Bottom, x, y);
                    switch (m_ParticleContainer[y][x].m_Type)
                    {
                        case(EParticleType::Sand):
                            UpdateSand(x, y);
                            break;
                        case(EParticleType::Water):
                            UpdateWater(x, y);
                            break;
                    }
                }
            }
        }

        for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
        {
            for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
            {
                m_ParticleContainer[y][x].m_HasBeenUpdated = false;
            }
        }
    }

    void LandscapeComponent::SpawnParticle(EParticleType type, int x, int y)
    {
        switch (type)
        {
            case(EParticleType::Sand):
                m_ParticleContainer[y][x] = PARTICLE_SAND;
                m_ParticleContainer[y][x].m_Color = GetColorForParticleType(EParticleType::Sand);
                break;
            case(EParticleType::Water):
                m_ParticleContainer[y][x] = PARTICLE_WATER;
                m_ParticleContainer[y][x].m_Color = GetColorForParticleType(EParticleType::Water);
                break;
        }
    }

    EParticleType LandscapeComponent::GetSurroundingParticleType(EDirection direction, unsigned int centerX, unsigned int centerY) const
    {
        EParticleType type = EParticleType::Border;
        switch (direction)
        {
            case(EDirection::TopLeft):
                if (centerX > 0 && centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
                {
                    type = m_ParticleContainer[centerY + 1][centerX - 1].m_Type;
                }
                break;
            case(EDirection::Top):
                if (centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
                {
                    type = m_ParticleContainer[centerY + 1][centerX].m_Type;
                }
                break;
            case(EDirection::TopRight):
                if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1 && centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
                {
                    type = m_ParticleContainer[centerY + 1][centerX - 1].m_Type;
                }
                break;
            case(EDirection::Left):
                if (centerX > 0)
                {
                    type = m_ParticleContainer[centerY][centerX - 1].m_Type;
                }
                break;
            case(EDirection::Right):
                if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1)
                {
                    type = m_ParticleContainer[centerY][centerX + 1].m_Type;
                }
                break;
            case(EDirection::BottomLeft):
                if (centerX > 0 && centerY > 0)
                {
                    type = m_ParticleContainer[centerY - 1][centerX - 1].m_Type;
                }
                break;
            case(EDirection::Bottom):
                if (centerY > 0)
                {
                    type = m_ParticleContainer[centerY - 1][centerX].m_Type;
                }
                break;
            case(EDirection::BottomRight):
                if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1 && centerY > 0)
                {
                    type = m_ParticleContainer[centerY - 1][centerX + 1].m_Type;
                }
                break;
        }

        return type;
    }

    void LandscapeComponent::DrawTexture()
    {
        m_Texture.release();
        GeneratePixels();
        m_Texture = std::make_unique<Texture>(m_Pixels, ALCHEMIST_LANDSCAPE_WIDTH, ALCHEMIST_LANDSCAPE_HEIGHT);
    }
    
    void LandscapeComponent::GeneratePixels()
    {
        for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
        {
            for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
            {
                Color particleColor = m_ParticleContainer[y][x].m_Color;
                unsigned int basePixelIndex = ((y * ALCHEMIST_LANDSCAPE_WIDTH) + x) * ALCHEMIST_PIXEL_DATA_SIZE;
                m_Pixels[basePixelIndex] = particleColor.GetRRatio();
                m_Pixels[basePixelIndex + 1] = particleColor.GetGRatio();
                m_Pixels[basePixelIndex + 2] = particleColor.GetBRatio();
            }
        }
    }

    Color LandscapeComponent::GetColorForParticleType(EParticleType type) const
    {
        Color color = COLOR_MAGENTA;
        switch (type)
        {
        case(EParticleType::Air):
            color = COLOR_BLACK;
            break;
        case(EParticleType::Water):
            color = COLOR_BLUE;
            break;
        case(EParticleType::Sand):
            Color sandColors[3]{
                Color{230, 179, 14},
                Color{166, 129, 24},
                Color{122, 94, 0},
            };
            color = sandColors[std::rand() % 3];
            break;
        }
        return color;
    }

    void LandscapeComponent::UpdateSand(unsigned int x, unsigned int y)
    {
        Particle currentParticle = m_ParticleContainer[y][x];
        if (GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Border && 
            GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Sand)
        {
            m_ParticleContainer[y][x] = PARTICLE_AIR;
            m_ParticleContainer[y - 1][x] = currentParticle;
        }
        else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Border 
            && GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Sand)
        {
            m_ParticleContainer[y][x] = PARTICLE_AIR;
            m_ParticleContainer[y - 1][x - 1] = currentParticle;
        }
        else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Border 
            && GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Sand)
        {
            m_ParticleContainer[y][x] = PARTICLE_AIR;
            m_ParticleContainer[y - 1][x + 1] = currentParticle;
        }
    }

    void LandscapeComponent::UpdateWater(unsigned int x, unsigned int y)
    {
        Particle currentParticle = m_ParticleContainer[y][x];
        if (GetSurroundingParticleType(EDirection::Bottom, x, y) == EParticleType::Air)
        {
            m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x];
            m_ParticleContainer[y - 1][x] = currentParticle;
        }
        else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) == EParticleType::Air)
        {
            m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x - 1];
            m_ParticleContainer[y - 1][x - 1] = currentParticle;
        }
        else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) == EParticleType::Air)
        {
            m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x + 1];
            m_ParticleContainer[y - 1][x + 1] = currentParticle;
        }
        else if (GetSurroundingParticleType(EDirection::Left, x, y) == EParticleType::Air)
        {
            m_ParticleContainer[y][x] = m_ParticleContainer[y][x - 1];
            m_ParticleContainer[y][x - 1] = currentParticle;
            
        }
        else if (GetSurroundingParticleType(EDirection::Right, x, y) == EParticleType::Air)
        {
            m_ParticleContainer[y][x] = m_ParticleContainer[y][x + 1];
            m_ParticleContainer[y][x + 1] = currentParticle;
        }
    }
}