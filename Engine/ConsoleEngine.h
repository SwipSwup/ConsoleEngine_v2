//
// Created by david on 20/05/2024.
//

#ifndef CONSOLEENGINE_V2_CONSOLEENGINE_H
#define CONSOLEENGINE_V2_CONSOLEENGINE_H

#include "Core/Scene/Scene.h"

namespace Engine
{
    class Window;
    class Renderer;

    struct EngineSettings
    {
        bool showFps = true;
        bool showRenderUpdates = false;

        int ticksPerSecond = 30;
        float fpsUpdateInterval = .1;

        unsigned int maxInputActionsPerFrame = 10;
    };

    class ConsoleEngine
    {
    public:
        ConsoleEngine();
        virtual ~ConsoleEngine();

        void Start();
        void Stop();

        static EngineSettings* settings;

    private:

        void Run();

        void Tick();

        void FixedTick();

        void TickScene(float deltaTime);
        void FixTickScene();

    public:
        void LoadSettings();
        void LoadSettings(EngineSettings* settings);

    private:
        Window* window;
        Renderer* renderer;
    };

} // Engine

#endif //CONSOLEENGINE_V2_CONSOLEENGINE_H
