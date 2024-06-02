//
// Created by david on 01/06/2024.
//

#include "Scene.h"
#include "../../Runtime/Objects/GameObject.h"

namespace Engine
{
    Scene::Scene(char* name)
    {
        this->name = name;
    }

    void Scene::OnSceneLoad(ConsoleEngine* engine)
    {
        this->engine = engine;
    }

    void Scene::Tick(float deltaTime)
    {
        for (GameObject* object : loadedGameObjects)
        {
            object->Tick(deltaTime);
        }
    }

    void Scene::FixTick()
    {
        for (GameObject* object : loadedGameObjects)
        {
            object->FixTick();
        }
    }

    void Scene::Spawn(GameObject* gameObject)
    {
        loadedGameObjects.push_back(gameObject);

        gameObject->SetScene(this);
        gameObject->OnSpawn();
    }

    ConsoleEngine* Scene::GetEngine()
    {
        return engine;
    }

    const char* Scene::GetName()
    {
        return name;
    }
} // Engine