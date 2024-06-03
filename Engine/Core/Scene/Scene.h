//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_SCENE_H
#define CONSOLEENGINE_V2_SCENE_H

#include <list>

namespace Engine
{

    class SceneManager;
    class GameObject;
    class CameraComponent;
    class Scene
    {
    public:
        Scene(char* name);

        void Load(SceneManager* engine);

        void Tick(float deltaTime);

        void FixTick();

    private:
        SceneManager* sceneManager;

        const char* name;

    public:
        const char* GetName();

    private:
        std::list<GameObject*> sceneObjects;

        std::list<GameObject*> loadedGameObjects;

    public:
        void Spawn(GameObject* gameObject);

        void Destroy(GameObject* gameObject);

        void AddSceneObject(GameObject* gameObject);

    private:
        CameraComponent* sceneCamera;

        void SpawnSceneObjects();

    public:
        CameraComponent* GetSceneCamera();

        void SetSceneCamera(CameraComponent* camera);
    };

} // Engine

#endif //CONSOLEENGINE_V2_SCENE_H
