#pragma once

#include "common/utils/BasicGameHandler.h"

using namespace ForgeEngine;

namespace Alchemist
{
    class Alchemist : public BasicGameHandler
    {
        using Mother = BasicGameHandler;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        /************************************/
        /**************METHODS***************/
        /************************************/
    public:
        Alchemist(std::string name, unsigned int width, unsigned int height);

    protected:
        virtual void OnInit() override;
        virtual void OnUpdate(float dT) override;
        virtual void OnTermination() override;

        virtual bool ShouldTerminate() override;
    };
}