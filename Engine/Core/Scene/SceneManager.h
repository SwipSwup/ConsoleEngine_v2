//
// Created by david on 02/06/2024.
//

#ifndef CONSOLEENGINE_V2_SCENEMANAGER_H
#define CONSOLEENGINE_V2_SCENEMANAGER_H

#include "Scene.h"

namespace Engine
{

    class ConsoleEngine;
    class SceneManager
    {
    public:
        void Intialize(ConsoleEngine* engine);

    private:
        Scene* activeScene;

        ConsoleEngine* engine;

    public:
        Scene* GetActiveScene();

        void LoadScene(Scene* scene);

        void UnloadScene();

        void TickActiveScene(float deltaTime);

        void FixTickActiveScene();
    };

} // Engine

#endif //CONSOLEENGINE_V2_SCENEMANAGER_H
