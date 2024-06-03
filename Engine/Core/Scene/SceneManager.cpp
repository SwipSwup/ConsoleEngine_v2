//
// Created by david on 02/06/2024.
//

#include "SceneManager.h"

namespace Engine
{
    void SceneManager::LoadScene(Scene* scene)
    {
        activeScene = scene;

        scene->Load(this);
    }

    void SceneManager::UnloadScene()
    {
        activeScene = nullptr;
    }

    void SceneManager::TickActiveScene(float deltaTime)
    {
        if(activeScene)
            activeScene->Tick(deltaTime);
    }

    void SceneManager::FixTickActiveScene()
    {
        if(activeScene)
            activeScene->FixTick();
    }

    void SceneManager::Intialize(ConsoleEngine* engine)
    {
        this->engine = engine;
    }

    Scene* SceneManager::GetActiveScene()
    {
        return activeScene;
    }
} // Engine