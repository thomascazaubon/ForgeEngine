#pragma once

#include "engine/core/World.h"

#include <string>

struct GLFWwindow;

namespace ForgeEngine
{
    class World;

    class GameHandler
    {
        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        public:
            static GameHandler* s_Instance;

        protected:
            GLFWwindow* m_Window{ nullptr };
            unsigned int m_WindowWidth;
            unsigned int m_WindowHeight;
            World m_World{};

        /************************************/
        /**************METHODS***************/
        /************************************/

        public:
            GameHandler(std::string name, unsigned int width, unsigned int height);
            //Handles the main loop
            void HandleProcess();

            GLFWwindow* GetWindow() const { return m_Window; }
            unsigned int GetWindowWidth() const { return m_WindowWidth; }
            void SetWindowWidth(unsigned int width) { m_WindowWidth = width; }
            unsigned int GetWindowHeight() const { return m_WindowHeight; }
            void SetWindowHeight(unsigned int height) { m_WindowHeight = height; }
            World& GetWorld() { return m_World; }

            static GameHandler& Get() { return *s_Instance; }

        protected:
            virtual void OnPreInit() {};
            virtual void OnInit() {};
            virtual void OnUpdatePreRender(float dT);
            virtual void OnUpdate(float dT) {}
            virtual void OnPostUpdate(float dT) {}
            virtual void OnTermination();

            virtual bool ShouldTerminate() = 0;
    };
}