//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_RENDERER_H
#define CONSOLEENGINE_V2_RENDERER_H

#include <windows.h>
#include "../../Runtime/Utility/Color/Color.h"

namespace Engine
{
    struct Sprite;
    struct RenderObject
    {
        RenderObject();
        RenderObject(wchar_t data, Color color);

        wchar_t data;
        Color color;
    };

    class Renderer
    {
    public:
        void Start();

        void Render();

        void SetConsoleHandle(HANDLE hConsole);

        void SetBufferSize(COORD size);

    private:
        COORD bufferSize;
        RenderObject* previousRenderBuffer{};
        RenderObject* renderBuffer{};
        HANDLE hConsole;
        int* zBufferIndex{};

        int TranslateToBufferIndex(int x, int y, int xDimension);

        void InitRenderBuffer();

        void ConsumeRenderBuffer();

        void WriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color);

        void ForceWriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color);

    public:
        void WDrawSprite(Sprite* sprite, int originX, int originY, int z);

        void WDrawText(const char* text, int originX, int originY, int z);

        void WDrawText(const char* text, Color color, int originX, int originY, int z);

        bool HasRenderObjectUpdated(int xy);

        void UpdateConsoleMode(DWORD mode, bool bEnable);
    };

} // Engine

#endif //CONSOLEENGINE_V2_RENDERER_H
