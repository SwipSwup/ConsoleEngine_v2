//
// Created by david on 20/05/2024.
//

#ifndef CONSOLEENGINE_V2_CONSOLEENGINE_H
#define CONSOLEENGINE_V2_CONSOLEENGINE_H

#include "Core/Scene/Scene.h"

namespace Engine
{
    class Window;

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
        void LoadSettings(EngineSettings settings);

    private:
        void LoadDefaultScene();

        void UpdateConsoleTitle(float deltaTime = 0);

    public:
        bool LoadScene(Scene* scene);

    private:

    public:
        Window* GetWindow();

        void LoadSettings(EngineSettings* settings);
    };

} // Engine

#endif //CONSOLEENGINE_V2_CONSOLEENGINE_H
