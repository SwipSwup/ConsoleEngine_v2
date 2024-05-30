//
// Created by david on 20/05/2024.
//

#include <iostream>
#include <thread>
#include "Window.h"

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

        if (!SetupMessageClass())
            return false;

        LoadConsoleFontInfo();

        WSetConsoleTitle("Console Engine");

        messageThread = std::thread(&Window::HandleMessages, this);

        ShowWindow(hwndConsole, SW_SHOW);
        return true;
    }

    LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_CLOSE:
                PostQuitMessage(0);
                return 0;
            case WM_KEYDOWN:
                std::cout << wParam << std::endl;
                if (wParam == VK_ESCAPE)
                {
                    PostQuitMessage(0);
                }
                break;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    void Window::WSetConsoleSize(short width, short height)
    {
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
        windowSize.Right = (short) (width / fontConsole.dwFontSize.X) - 1;
        windowSize.Bottom = (short) (height / fontConsole.dwFontSize.Y) - 1;

        // Make sure the console window size fits within the new buffer size
        COORD bufferSize;
        bufferSize.X = (short) (width / fontConsole.dwFontSize.X);
        bufferSize.Y = (short) (height / fontConsole.dwFontSize.Y);

        if (!SetConsoleScreenBufferSize(hConsole, bufferSize))
        {
            std::cerr << "Error setting console screen buffer size: " << GetLastError() << std::endl;
            return;
        }

        if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
        {
            std::cerr << "Error setting console window size: " << GetLastError() << std::endl;
            return;
        }

        for (int i = 0; i < width / fontConsole.dwFontSize.X; ++i)
        {
            std::cout << "#";
        }
    }

    void Window::WSetConsoleTitle(char* title)
    {
        if (hwndConsole)
        {
            SetConsoleTitle(TEXT(title));
        }
    }

    bool Window::SetupMessageClass()
    {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = TEXT("ConsoleClass");

        if (!RegisterClass(&wc))
        {
            std::cerr << "Failed to register window class." << std::endl;
            return false;
        }

        return true;
    }

    void Window::RedirectIO() {
        FILE* fp;

        // Redirect STDOUT to the new console
        freopen_s(&fp, "CONOUT$", "w", stdout);

        // Redirect STDERR to the new console
        freopen_s(&fp, "CONOUT$", "w", stderr);

        // Redirect STDIN to the new console
        freopen_s(&fp, "CONIN$", "r", stdin);

        std::cout << "Console allocated and I/O redirected." << std::endl;
    }

    void Window::LoadConsoleFontInfo()
    {
        fontConsole.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        GetCurrentConsoleFontEx(hConsole, FALSE, &fontConsole);
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

        messageThread.join();
    }

    void Window::WShowWindow()
    {

    }

    void Window::HandleMessages()
    {
        MSG msg;
            std::cout << "a" << std::endl;
        //std::cout << GetMessage(&msg, hwndConsole, 0, 0) << std::endl;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            std::cout << msg.message << std::endl;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        std::cout << "end";
    }

} // Engine