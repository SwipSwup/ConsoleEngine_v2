//
// Created by david on 20/05/2024.
//

#include <iostream>
#include <thread>
#include "Window.h"
#include "../RenderSystem/Renderer.h"

namespace Engine
{
    Window::Window()
    {
        CreateConsoleWindow();
    }

    bool Window::CreateConsoleWindow()
    {
        AllocConsole();
        //redirectIO();
        hwndConsole = GetConsoleWindow();
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!hwndConsole || !hConsole) return false;

        if (!GetConsoleMode(hConsole, &dwMode))
        {
            std::cerr << "[Window] Error getting console mode" << std::endl;
            return false;
        }

        RedirectIO();

        LoadConsoleFontInfo();

        WSetConsoleTitle("Console Engine");
        //360 360
        WSetConsoleSize(1000, 1000);

        WUpdateConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING, true);

        WShowWindow();
        return true;
    }

    void Window::WUpdateConsoleMode(DWORD mode, bool bEnable)
    {
        if (bEnable)
        {
            dwMode |= mode;
        }
        else
        {
            dwMode &= ~mode;
        }

        if (!SetConsoleMode(hConsole, dwMode))
        {
            std::cerr << "[Window] Error setting console mode" << std::endl;
        }
    }

    void Window::WSetConsoleTitle(char* title)
    {
        if (hwndConsole)
        {
            SetConsoleTitle(TEXT(title));
        }
    }

    void Window::RedirectIO()
    {
        FILE* fp;

        // Redirect STDOUT to the new console
        freopen_s(&fp, "CONOUT$", "w", stdout);

        // Redirect STDERR to the new console
        //freopen_s(&fp, "CONOUT$", "w", stderr);

        // Redirect STDIN to the new console
        freopen_s(&fp, "CONIN$", "r", stdin);
    }

    void Window::LoadConsoleFontInfo()
    {
        //CONSOLE_FONT_INFOEX cfi;
        fontConsole.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        fontConsole.nFont = 0;
        fontConsole.dwFontSize.X = 8;
        fontConsole.dwFontSize.Y = 16;
        fontConsole.FontFamily = FF_DONTCARE;
        fontConsole.FontWeight = FW_NORMAL;
        wcscpy_s(fontConsole.FaceName, L"Consolas");
        SetCurrentConsoleFontEx(hConsole, FALSE, &fontConsole);

        //fontConsole.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        //GetCurrentConsoleFontEx(hConsole, FALSE, &fontConsole);
    }

    void Window::DestroyConsoleWindow()
    {
        if (hwndConsole)
        {
            FreeConsole();
            hwndConsole = nullptr;
            hConsole = nullptr;
            std::cout << "Console closed." << std::endl;
        }
    }

    void Window::WShowWindow()
    {
        ShowWindow(hwndConsole, SW_SHOW);
    }

    void Window::WHideWindow()
    {
        ShowWindow(hwndConsole, SW_HIDE);
    }

    void Window::WSetConsoleSize(short width, short height)
    {
        windowSize = {width, height};
        if (!renderer)
            renderer->SetBufferSize(GetWindowCharacterSize());

        if (hwndConsole)
        {
            MoveWindow(hwndConsole, 0, 0, 0, 0, TRUE);
        }
        else
        {
            std::cerr << "Error getting console window handle: " << GetLastError() << std::endl;
        }

        SMALL_RECT windowSize;
        windowSize.Left = 0;
        windowSize.Top = 0;
        windowSize.Right = (short) (width / fontConsole.dwFontSize.X - 1);
        windowSize.Bottom = (short) (height / fontConsole.dwFontSize.Y - 1);

        COORD bufferSize;
        bufferSize.X = (short) (width / fontConsole.dwFontSize.X);
        bufferSize.Y = (short) (height / fontConsole.dwFontSize.Y);

        // Make sure the console window size fits within the new buffer size
        if (!SetConsoleScreenBufferSize(hConsole, bufferSize))
        {
            std::cerr << "[Window] Error setting console screen buffer size: {X: " << bufferSize.X << ", Y:"
                      << bufferSize.Y << "}" << std::endl;
            return;
        }

        if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
        {
            std::cerr << "[Window] Error setting console window size: " << GetLastError() << std::endl;
            return;
        }
    }

    void Window::WRegisterRenderer(Renderer* renderer)
    {
        this->renderer = renderer;

        renderer->SetConsoleHandle(renderer);
        renderer->SetBufferSize(GetWindowCharacterSize());
    }

    COORD Window::GetWindowCharacterSize()
    {
        return {(short) (windowSize.X / fontConsole.dwFontSize.X), (short) (windowSize.Y / fontConsole.dwFontSize.Y)};
    }

    COORD Window::GetWindowPixelSize()
    {
        return windowSize;
    }


} // Engine