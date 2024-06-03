//
// Created by david on 02/06/2024.
//

#ifndef CONSOLEENGINE_V2_SPRITERENDERCOMPONENT_H
#define CONSOLEENGINE_V2_SPRITERENDERCOMPONENT_H

#include "../../Component.h"

namespace Engine
{

    struct Sprite;
    class CameraComponent;
    class SpriteRenderComponent : public Component
    {
    private:
        CameraComponent* camera_ref;

    public:
        Sprite* sprite_ref;

        void Tick(float deltaTime) override;

        void OnSpawn() override;
    };

} // Engine

#endif //CONSOLEENGINE_V2_SPRITERENDERCOMPONENT_H
