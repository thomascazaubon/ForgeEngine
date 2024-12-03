#pragma once

#include "engine/core/GameHandler.h"

namespace ForgeEngine
{
    class BasicGameHandler : public GameHandler
    {
        using Mother = GameHandler;
        using Mother::Mother;

    protected:
        virtual void OnInit() override;
        virtual void OnUpdate(float dT) override;

        virtual bool ShouldTerminate() override;
    };
}