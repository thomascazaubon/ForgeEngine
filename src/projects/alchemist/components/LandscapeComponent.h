#pragma once

#include "engine/components/Component.h"
#include "engine/math/Vector2.h"
#include "engine/render/Color.h"

#include <memory>

namespace ForgeEngine
{
    class Texture;
}

using namespace ForgeEngine;

namespace Alchemist
{
    #define ALCHEMIST_WINDOW_WIDTH 1280
    #define ALCHEMIST_WINDOW_HEIGHT 720
    #define ALCHEMIST_LANDSCAPE_WIDTH 320
    #define ALCHEMIST_LANDSCAPE_HEIGHT 180
    #define ALCHEMIST_PIXEL_DATA_SIZE 3

    #define PARTICLE_AIR Particle{}
    #define PARTICLE_SAND Particle{EParticleType::Sand, COLOR_MAGENTA, false}
    #define PARTICLE_WATER Particle{EParticleType::Water, COLOR_MAGENTA, false}

    struct ParticlePosition
    {
        unsigned short x;
        unsigned short y;
    };

    enum class EParticleType
    {
        Border,
        Air,
        Water,
        Sand
    };

    enum class EDirection
    {
        TopLeft,
        Top,
        TopRight,
        Left,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    struct Particle
    {
        EParticleType m_Type = EParticleType::Air;
        Color m_Color = COLOR_BLACK;
        bool m_HasBeenUpdated = false;
    };

    class LandscapeComponent : public Component
    {
        using Mother = Component;

        public:
            virtual bool OnPreInit() override;
            virtual void OnUpdatePreRender(float dT) override;

#ifdef FORGE_DEBUG_ENABLED
            virtual void OnDrawDebug(float dT) const override;
            const char* GetDebugName() const override { return "LandscapeComponent"; }
#endif //FORGE_DEBUG_ENABLED

            void SpawnParticle(EParticleType type, int x, int y);

        private:
            EParticleType GetSurroundingParticleType(EDirection direction, unsigned int centerX, unsigned int centerY) const;
            void UpdateParticles();
            void DrawTexture();
            Color GetColorForParticleType(EParticleType type) const;
            void GeneratePixels();
            Vector2 GetMousePosition() const;

            void UpdateSand(unsigned int x, unsigned int y);
            void UpdateWater(unsigned int x, unsigned int y);

        private:
            using ParticleContainer = Particle[ALCHEMIST_LANDSCAPE_HEIGHT][ALCHEMIST_LANDSCAPE_WIDTH];

            ParticleContainer m_ParticleContainer;
            float m_Pixels[ALCHEMIST_LANDSCAPE_WIDTH * ALCHEMIST_LANDSCAPE_HEIGHT * ALCHEMIST_PIXEL_DATA_SIZE];
            std::unique_ptr<Texture> m_Texture;
    };
}