//
// Created by david on 03/06/2024.
//

#include <iostream>
#include "CameraController.h"
#include "ConsoleEngine.h"
#include "Core/InputSystem/InputSystem.h"
#include "Runtime/Utility/Vector/Vector3D.h"

namespace Game
{
    void CameraController::Tick(float deltaTime)
    {
        Component::Tick(deltaTime);

        if(Engine::ConsoleEngine::inputSystem->KeyPressed('W')) {
            *GetPosition() += Engine::Vector3D(0, 1, 0) * deltaTime * 10;
        }

        if(Engine::ConsoleEngine::inputSystem->KeyPressed('A')) {
            *GetPosition() += Engine::Vector3D(-1, 0, 0) * deltaTime * 10;
        }

        if(Engine::ConsoleEngine::inputSystem->KeyPressed('S')) {
            *GetPosition() += Engine::Vector3D(0, -1, 0) * deltaTime * 10;
        }

        if(Engine::ConsoleEngine::inputSystem->KeyPressed('D')) {
            *GetPosition() += Engine::Vector3D(1, 0, 0) * deltaTime * 10;
        }
    }
} // Game