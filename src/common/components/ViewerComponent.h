#pragma once

#include "engine/components/Component.h"

namespace ForgeEngine
{
    class ViewerComponent : public Component
    {
        using Mother = Component;

        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        private:
            float m_TranslationSpeed;
            float m_RotationSpeed;
            float m_ScaleSpeed;
            
        /************************************/
        /**************METHODS***************/
        /************************************/
        public:
            ViewerComponent(float translationSpeed, float rotationSpeed, float scaleSpeed);

            virtual void OnUpdate(float dT) override;

            float GetRotationSpeed() const { return m_RotationSpeed; }
            void SetRotationSpeed(float rotationSpeed) { m_RotationSpeed = rotationSpeed; }
    };
}