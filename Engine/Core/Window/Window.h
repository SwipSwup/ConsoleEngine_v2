//
// Created by david on 20/05/2024.
//

#ifndef CONSOLEENGINE_V2_WINDOW_H
#define CONSOLEENGINE_V2_WINDOW_H

#include <windows.h>
#include "thread"

namespace Engine
{
    class Renderer;
    class Window
    {
    public:
        Window();

    private:
        bool CreateConsoleWindow();

        void DestroyConsoleWindow();

        void LoadConsoleFontInfo();

        void RedirectIO();

    public:
        void WRegisterRenderer(Renderer* renderer);

        void WUpdateConsoleMode(DWORD mode, bool bEnable);

        void WSetConsoleSize(short width, short height);

        void WSetConsoleTitle(char* title);

        void WShowWindow();

        void WHideWindow();


    private:
        DWORD dwMode{};

        HWND hwndConsole;
        HANDLE hConsole;
        CONSOLE_FONT_INFOEX fontConsole;
        COORD windowSize;

        Renderer* renderer;

    public:
        COORD GetWindowPixelSize();
        COORD GetWindowCharacterSize();


    };

} // Engine

#endif //CONSOLEENGINE_V2_WINDOW_H
