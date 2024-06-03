//
// Created by david on 01/06/2024.
//

#include <iostream>
#include "Scene.h"
#include "Runtime/Objects/GameObject.h"
#include "SceneManager.h"

namespace Engine
{
    Scene::Scene(char* name)
    {
        this->name = name;
    }

    void Scene::Load(SceneManager* sceneManager)
    {
        this->sceneManager = sceneManager;

        SpawnSceneObjects();
    }

    void Scene::Tick(float deltaTime)
    {
        for (GameObject* object: loadedGameObjects)
        {
            object->Tick(deltaTime);
        }
    }

    void Scene::FixTick()
    {
        for (GameObject* object: loadedGameObjects)
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

    const char* Scene::GetName()
    {
        return name;
    }

    void Scene::AddSceneObject(GameObject* gameObject)
    {
        sceneObjects.push_back(gameObject);
    }

    void Scene::Destroy(GameObject* gameObject)
    {
        loadedGameObjects.remove(gameObject);
    }

    CameraComponent* Scene::GetSceneCamera()
    {
        return sceneCamera;
    }

    void Scene::SetSceneCamera(CameraComponent* camera)
    {
        sceneCamera = camera;
    }

    void Scene::SpawnSceneObjects()
    {
        for (GameObject* item: sceneObjects)
        {
            Spawn(item);
        }
    }
} // Engine