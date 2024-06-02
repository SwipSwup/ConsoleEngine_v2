//
// Created by david on 20/05/2024.
//

#ifndef CONSOLEENGINE_V2_WINDOW_H
#define CONSOLEENGINE_V2_WINDOW_H

#include <windows.h>
#include "thread"

namespace Engine
{
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
        void WSetConsoleSize(short width, short height);

        void WSetConsoleTitle(char* title);

        void WShowWindow();

        void WHideWindow();
    private:
        HWND hwndConsole;
        HANDLE hConsole;
        CONSOLE_FONT_INFOEX fontConsole;

    };

} // Engine

#endif //CONSOLEENGINE_V2_WINDOW_H
