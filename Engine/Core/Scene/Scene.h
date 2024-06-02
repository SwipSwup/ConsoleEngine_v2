//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_SCENE_H
#define CONSOLEENGINE_V2_SCENE_H

#include <list>

namespace Engine
{

    class ConsoleEngine;
    class GameObject;
    class Scene
    {
    public:
        Scene(char* name);

        void OnSceneLoad(ConsoleEngine* engine);

        void Tick(float deltaTime);

        void FixTick();

    private:
        ConsoleEngine* engine;

        const char* name;

    public:
        ConsoleEngine* GetEngine();

        const char* GetName();

    private:
        std::list<GameObject*> loadedGameObjects;

    public:
        void Spawn(GameObject* gameObject);
    };

} // Engine

#endif //CONSOLEENGINE_V2_SCENE_H
