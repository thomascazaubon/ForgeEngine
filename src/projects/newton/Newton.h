#pragma once

#include "common/utils/BasicGameHandler.h"

using namespace ForgeEngine;

namespace Newton
{
    class Newton : public BasicGameHandler
    {
        using Mother = BasicGameHandler;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        /************************************/
        /**************METHODS***************/
        /************************************/
    public:
        Newton(std::string name, unsigned int width, unsigned int height);

    protected:
        virtual void OnInit() override;
        virtual void OnUpdate(float dT) override;
        virtual void OnTermination() override;

        virtual bool ShouldTerminate() override;
    };
}