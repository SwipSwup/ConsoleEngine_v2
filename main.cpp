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
#include "Game/Player/CameraController.h"


int main()
{
    Engine::ConsoleEngine engine = Engine::ConsoleEngine();

    Engine::Scene scene = Engine::Scene("test");

    Engine::GameObject camera = Engine::GameObject("Camera");
    camera.AddComponent<Engine::CameraComponent>();
    camera.AddComponent<Game::CameraController>();

    scene.AddSceneObject(&camera);


    Engine::GameObject object = Engine::GameObject("Object");
    Engine::SpriteRenderComponent* srComp = object.AddComponent<Engine::SpriteRenderComponent>();

    wchar_t** texture = new wchar_t* [3]
            {
                    new wchar_t[3]{'+', '^', '+',},
                    new wchar_t[3]{'|', ' ', '>',},
                    new wchar_t[3]{'+', '-', '+',}
            };

    Engine::Color** color = new Engine::Color* [3]
            {
                    new Engine::Color[3]{Engine::Color::BLU, Engine::Color::RED, Engine::Color::BLU},
                    new Engine::Color[3]{Engine::Color::BLU, Engine::Color::BLU, Engine::Color::GRN},
                    new Engine::Color[3]{Engine::Color::BLU, Engine::Color::BLU, Engine::Color::BLU},
            };

    Engine::Sprite* sprite = new Engine::Sprite(texture, color, Engine::Vector2D(3, 3));

    srComp->sprite_ref = sprite;

    scene.AddSceneObject(&object);


    Engine::ConsoleEngine::sceneManager->LoadScene(&scene);


    for (int i = 0; i < 50; ++i)
    {
    Engine::GameObject* obj = scene.Spawn(&object);

    obj->position = new Engine::Vector3D(rand()%101, rand()%101, 0);

    }


    engine.Start();


    while (true);

    return 0;
}
