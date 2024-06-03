//
// Created by david on 03/06/2024.
//

#ifndef CONSOLEENGINE_V2_CAMERACONTROLLER_H
#define CONSOLEENGINE_V2_CAMERACONTROLLER_H

#include "Runtime/Objects/Component/Component.h"

namespace Game
{

    class CameraController : public Engine::Component
    {
        void Tick(float deltaTime) override;
    };

} // Game

#endif //CONSOLEENGINE_V2_CAMERACONTROLLER_H
