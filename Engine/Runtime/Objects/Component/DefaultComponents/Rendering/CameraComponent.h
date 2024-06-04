//
// Created by david on 02/06/2024.
//

#ifndef CONSOLEENGINE_V2_CAMERACOMPONENT_H
#define CONSOLEENGINE_V2_CAMERACOMPONENT_H

#include "Runtime/Objects/Component/Component.h"

namespace Engine
{

    class Renderer;
    struct Sprite;
    struct Vector3D;
    class CameraComponent : public Component
    {
    private:
        Renderer* renderer_ref;

    public:
        void OnSpawn() override;

        void DrawSprite(Sprite* sprite, Vector3D* position);

        Component* Clone() override;

    };

} // Engine

#endif //CONSOLEENGINE_V2_CAMERACOMPONENT_H
