//
// Created by david on 20/05/2024.
//

#include <chrono>
#include "ConsoleEngine.h"

namespace Engine
{
    EngineSettings* ConsoleEngine::settings = new EngineSettings();

    ConsoleEngine::ConsoleEngine()
    {
        /*this->window = new Window(100, 30);
        this->debugConsole = new Debug();
        this->inputSystem = new InputSystem();

        activeScene = nullptr;*/

        /* TODO
         * Create Window
         * Setup Renderer
         * Create SceneManager
         * Setup Default Scene
         */
    }

    ConsoleEngine::~ConsoleEngine()
    {
        /*delete window;
        delete debugConsole;
        delete settings;*/
    }

    std::chrono::steady_clock::time_point previousTimePoint;
    std::chrono::steady_clock::time_point fixedTickTimePoint;


    void ConsoleEngine::Start()
    {
        previousTimePoint = fixedTickTimePoint = std::chrono::steady_clock::now();

        /*if (activeScene == nullptr)
            LoadDefaultScene();*/

        LoadSettings();

        Run();
    }

    void ConsoleEngine::Stop()
    {
    }

    void ConsoleEngine::Run()
    {


        while (true)
        {
            Tick();

            //TODO Render
            //window->Render();

        }
    }

    void ConsoleEngine::Tick()
    {
        std::chrono::steady_clock::time_point currentTimePoint = std::chrono::steady_clock::now();
        TickScene((float) (currentTimePoint - previousTimePoint).count() / 1000000000.f);

        previousTimePoint = currentTimePoint;

        //std::cout << (currentTimePoint - previousTimePoint).count() << std::endl;

        if ((currentTimePoint - fixedTickTimePoint).count() < std::chrono::duration_cast<
                std::chrono::steady_clock::duration>(
                std::chrono::duration<float>(1.0f / settings->ticksPerSecond)).count())
        {
            fixedTickTimePoint = std::chrono::steady_clock::now();
            return;
        }

        FixedTick();
        //std::cout << currentTimePoint.time_since_epoch().count();
    }

    void ConsoleEngine::FixedTick()
    {
        FixTickScene();
    }

    float tCounter = 0;

    void ConsoleEngine::TickScene(float deltaTime)
    {
        //activeScene->Tick(deltaTime);

        if ((tCounter += deltaTime) >= settings->fpsUpdateInterval)
        {
            tCounter = 0;
            UpdateConsoleTitle(deltaTime);
        }
    }

    void ConsoleEngine::FixTickScene()
    {
        //activeScene->FixTick();
    }

    void ConsoleEngine::LoadSettings()
    {
        //window->ShowRenderUpdates(settings->showRenderUpdates);
    }

    void ConsoleEngine::LoadSettings(EngineSettings* settings)
    {
        delete this->settings;
        this->settings = settings;
        LoadSettings();
    }

    void ConsoleEngine::UpdateConsoleTitle(float deltaTime)
    {
        //todo do this in the title
        //std::string title = activeScene->GetName();

        if (settings->showFps)
        {
            //title += " | FPS: " + std::to_string((int) (1 / deltaTime));
        }
        //window->UpdateConsoleTitle(title.c_str());
    }

    /*bool ConsoleEngine::LoadScene(Scene* scene)
    {
        if (scene == nullptr)
        {
            return false;
        }

        scene->OnSceneLoad(this);
        activeScene = scene;
        UpdateConsoleTitle();
        return true;
    }*/
} // Engine