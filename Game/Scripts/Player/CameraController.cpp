//
// Created by david on 03/06/2024.
//

#include <iostream>
#include <windows.h>
#include <sstream>
#include "CameraController.h"
#include "ConsoleEngine.h"
#include "Core/InputSystem/InputSystem.h"
#include "Core/RenderSystem/Renderer.h"
#include "Runtime/Utility/Vector/Vector3D.h"
#include "Runtime/Objects/GameObject.h"

namespace Game
{
    void CameraController::Tick(float deltaTime)
    {
        std::ostringstream os;
        os << "x: " << root_ref->position->x << " y: " << root_ref->position->y;

        Engine::ConsoleEngine::renderer->WDrawText(os.str().c_str(), 0, 0, 1000);

        Component::Tick(deltaTime);

        //TODO look into inverted position
        float movementSpeed = -20;
        //TODO implement wrapper for virtual keys
        if (Engine::InputSystem::KeyPressed(VK_SHIFT))
        {
            movementSpeed -= 30;
        }

        if (Engine::InputSystem::KeyPressed('W'))
        {
            *GetPosition() += Engine::Vector3D(0, 1, 0) * deltaTime * movementSpeed;
        }

        if (Engine::InputSystem::KeyPressed('A'))
        {
            *GetPosition() += Engine::Vector3D(-1, 0, 0) * deltaTime * movementSpeed;
        }

        if (Engine::InputSystem::KeyPressed('S'))
        {
            *GetPosition() += Engine::Vector3D(0, -1, 0) * deltaTime * movementSpeed;
        }

        if (Engine::InputSystem::KeyPressed('D'))
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