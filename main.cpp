#include <iostream>
#include <windows.h>
#include "Core/Window/Window.h"
#include "ConsoleEngine.h"
#include "Core/Scene/Scene.h"
#include "Core/Scene/SceneManager.h"
#include "Runtime/Objects/GameObject.h"
#include "Runtime/Objects/Component/DefaultComponents/Rendering/CameraComponent.h"
#include "Runtime/Objects/Component/DefaultComponents/Rendering/SpriteRenderComponent.h"
#include "Runtime/Utility/Color/Color.h"
#include "Runtime/Utility/Sprite/Sprite.h"
#include "Runtime/Utility/Vector/Vector2D.h"
#include "Runtime/Utility/Vector/Vector3D.h"
#include "Game/Scripts/Player/CameraController.h"


Engine::Scene* CreateDemoSceneOne()
{

}

void SpawnObjectRdm(Engine::Scene* scene, char* pathTexture, char* pathColor, int amount, int space, int z)
{
    Engine::GameObject object = Engine::GameObject(pathTexture);
    Engine::SpriteRenderComponent* srComp = object.AddComponent<Engine::SpriteRenderComponent>();
    Engine::Sprite* sprite = new Engine::Sprite();
    sprite->Load2DTextureFromFile(pathTexture);
    sprite->Load2DColorFromFile(pathColor);
    //sprite->Load2DColor(color);
    srComp->sprite_ref = sprite;

    for (int i = 0; i < amount; ++i)
    {
        Engine::GameObject* obj = scene->Spawn(&object);

        obj->position = new Engine::Vector3D(rand() % (space + 1) - space / 2, rand() % (space + 1) - space / 2, z);
    }
}

int main()
{
    srand (time(nullptr));
    Engine::ConsoleEngine engine = Engine::ConsoleEngine();

    Engine::Scene scene = Engine::Scene("test");

    Engine::GameObject camera = Engine::GameObject("Camera");
    camera.AddComponent<Engine::CameraComponent>();
    camera.AddComponent<Game::CameraController>();

    scene.AddSceneObject(&camera);


    Engine::GameObject campSite = new Engine::GameObject("campSite");
    campSite.position = new Engine::Vector3D(Engine::ConsoleEngine::window->GetWindowCharacterSize().X / 2,
                                             Engine::ConsoleEngine::window->GetWindowCharacterSize().Y / 2, 8);
    Engine::SpriteRenderComponent* srComp = campSite.AddComponent<Engine::SpriteRenderComponent>();
    Engine::Sprite* spriteCamp = new Engine::Sprite();
    spriteCamp->Load2DTextureFromFile(
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Structures\\T_CampSite.txt");
    spriteCamp->Load2DColorFromFile(
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Structures\\T_CampSite_Color.png");
    srComp->sprite_ref = spriteCamp;

    scene.AddSceneObject(&campSite);

    Engine::ConsoleEngine::sceneManager->LoadScene(&scene);

    SpawnObjectRdm(
            &scene,
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Tree\\T_Tree.txt",
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Tree\\T_Tree_Color.png",
            50,
            500,
            20
    );

    SpawnObjectRdm(
            &scene,
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Nature\\T_Grass.txt",
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Nature\\T_Grass_Color.png",
            2000,
            500,
            5
    );

    SpawnObjectRdm(
            &scene,
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Nature\\T_Pond.txt",
            "G:\\FH\\Sem2\\PROGR\\ConsoleEngine_v2\\Game\\Assets\\Textures\\Nature\\T_Pond_Color.png",
            20,
            500,
            6
    );

    engine.Start();


    while (true);

    return 0;
}
