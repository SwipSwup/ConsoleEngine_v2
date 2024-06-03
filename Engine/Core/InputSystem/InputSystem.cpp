//
// Created by david on 03/06/2024.
//

#include <windows.h>
#include "InputSystem.h"
namespace Engine
{
    bool InputSystem::KeyPressed(char key)
    {
        return GetAsyncKeyState(toupper(key)) & 0x8000;
    }
} // Engine