//
// Created by david on 02/06/2024.
//

#include <iostream>
#include "CameraComponent.h"
#include "ConsoleEngine.h"
#include "Core/RenderSystem/Renderer.h"
#include "Core/Scene/SceneManager.h"
#include "Runtime/Utility/Vector/Vector3D.h"
#include "Runtime/Objects/GameObject.h"

namespace Engine
{
    void CameraComponent::OnSpawn()
    {
        Component::OnSpawn();

        renderer_ref = ConsoleEngine::renderer;
        ConsoleEngine::sceneManager->GetActiveScene()->SetSceneCamera(this);

    }

    void CameraComponent::DrawSprite(Sprite* sprite, Vector3D* position)
    {

        renderer_ref->WDrawSprite(
                sprite,
                position->x + root_ref->position->x,
                position->y + root_ref->position->y,
                position->z
        );
    }
} // Engine