#pragma once

#include "engine/core/GameHandler.h"

using namespace ForgeEngine;

namespace ForgeEngine
{
    class Entity;
}

namespace Torch
{
    class Torch : public GameHandler
    {
        using Mother = GameHandler;

        public:
            Torch(std::string name, unsigned int width, unsigned int height);

        protected:
            virtual void OnInit() override;
            virtual void OnUpdate(float dT) override;
            virtual void OnTermination() override;

            virtual bool ShouldTerminate() override;

        private:
            ForgeEngine::Entity* m_Light;
            ForgeEngine::Entity* m_Cube;
    };
}