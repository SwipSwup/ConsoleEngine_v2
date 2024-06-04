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

        //TODO there is something wrong
        float movementSpeed = -10;

        if (Engine::ConsoleEngine::inputSystem->KeyPressed('H'))
        {
            movementSpeed += 30;
        }

        if (Engine::ConsoleEngine::inputSystem->KeyPressed('W'))
        {
            *GetPosition() += Engine::Vector3D(0, 1, 0) * deltaTime * movementSpeed;
        }

        if (Engine::ConsoleEngine::inputSystem->KeyPressed('A'))
        {
            *GetPosition() += Engine::Vector3D(-1, 0, 0) * deltaTime * movementSpeed;
        }

        if (Engine::ConsoleEngine::inputSystem->KeyPressed('S'))
        {
            *GetPosition() += Engine::Vector3D(0, -1, 0) * deltaTime * movementSpeed;
        }

        if (Engine::ConsoleEngine::inputSystem->KeyPressed('D'))
        {
            *GetPosition() += Engine::Vector3D(1, 0, 0) * deltaTime * movementSpeed;
        }
    }

    Engine::Component* CameraController::Clone()
    {
        CameraController* newComponent = new CameraController();
        newComponent->SetComponentData(this);
        return newComponent;
    }
} // Game