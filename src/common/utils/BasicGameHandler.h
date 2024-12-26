#pragma once

#include "engine/core/GameHandler.h"

namespace ForgeEngine
{
    class BasicGameHandler : public GameHandler
    {
        using Mother = GameHandler;
        using Mother::Mother;

    protected:
        virtual void OnPreInit() override;
        virtual void OnUpdatePreRender(float dT) override;

        virtual bool ShouldTerminate() override;
    };
}