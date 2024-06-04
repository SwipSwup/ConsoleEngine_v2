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

    GameObject* Scene::Spawn(GameObject* gameObject)
    {
        //TODO create new instance of the gameObject

        GameObject* object = gameObject->Clone(gameObject);
        loadedGameObjects.push_back(object);


        object->SetScene(this);
        object->OnSpawn();


        return object;

        /*loadedGameObjects.push_back(gameObject);

        gameObject->SetScene(this);
        gameObject->OnSpawn();

        return gameObject;*/
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
        for (GameObject* object: sceneObjects)
        {

            Spawn(object);
        }
    }
} // Engine