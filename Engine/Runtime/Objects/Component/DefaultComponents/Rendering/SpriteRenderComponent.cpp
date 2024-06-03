//
// Created by david on 02/06/2024.
//

#include <iostream>
#include "SpriteRenderComponent.h"
#include "ConsoleEngine.h"
#include "Core/Scene/SceneManager.h"
#include "Runtime/Objects/Component/DefaultComponents/Rendering/CameraComponent.h"
#include "Runtime/Objects/GameObject.h"
#include "Runtime/Utility/Vector/Vector3D.h"

namespace Engine
{
    void SpriteRenderComponent::Tick(float deltaTime)
    {
        Component::Tick(deltaTime);

        if(camera_ref)
            camera_ref->DrawSprite(sprite_ref, GetPosition());
    }

    void SpriteRenderComponent::OnSpawn()
    {
        Component::OnSpawn();

        camera_ref = ConsoleEngine::sceneManager->GetActiveScene()->GetSceneCamera();

        if(!camera_ref)
            std::cerr << "[SpriteRenderComponent] No camera in scene" << std::endl;
    }
} // Engine