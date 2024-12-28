#pragma once

#include "common/utils/BasicGameHandler.h"

using namespace ForgeEngine;

namespace ForgeEngine
{
    class Entity;
}

namespace Cartographer
{
    class Cartographer : public BasicGameHandler
    {
        using Mother = BasicGameHandler;

    public:
        Cartographer(std::string name, unsigned int width, unsigned int height);

    protected:
        virtual void OnInit() override;
        virtual void OnTermination() override;

        virtual bool ShouldTerminate() override;
    };
}