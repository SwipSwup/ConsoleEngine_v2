#include <iostream>
#include "Engine/Core/Window/Window.h"

int main()
{
    Engine::Window w = Engine::Window();

    w.WSetConsoleSize(1100, 800);
    //std::cout << "Hello, World!" << std::endl;
    while(true);
    return 0;
}
