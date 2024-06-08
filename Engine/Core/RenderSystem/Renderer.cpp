//
// Created by david on 01/06/2024.
//

#include <cstring>
#include <iostream>
#include "Renderer.h"
#include "../../Runtime/Utility/Sprite/Sprite.h"
#include "../../Runtime/Utility/Vector/Vector2D.h"

namespace Engine
{
    RenderObject::RenderObject() : color(Color::WHT)
    {
        data = ' ';
    }

    RenderObject::RenderObject(wchar_t data, Color color) : color(color)
    {
        this->data = data;
    }

    int Renderer::TranslateToBufferIndex(int x, int y, int xDimension)
    {
        return x + y * xDimension;
    }

    void Renderer::SetConsoleHandle(HANDLE hConsole)
    {
        this->hConsole = hConsole;
    }

    void Renderer::SetBufferSize(COORD size)
    {
        //this->bufferSize = {10, 10};

        //125, 62
        this->bufferSize = size;
    }

    //TODO create 4 thread and split console into 4 sections
    void Renderer::Render()
    {
        DWORD charsWritten;

        for (int y = 0; y < bufferSize.Y; ++y)
        {
            for (int x = 0; x < bufferSize.X; ++x)
            {
                int bufferIndex = TranslateToBufferIndex(x, y, bufferSize.X);
                //if (!updateBuffer[bufferIndex])

                if (!HasRenderObjectUpdated(bufferIndex))
                {
                    continue;
                }
                RenderObject obj = renderBuffer[bufferIndex];

                Color c = obj.color;

                SetConsoleCursorPosition(hConsole, COORD{(SHORT) x, (SHORT) y});
                if (!WriteConsoleA(
                        hConsole,
                        c.GetEscapeCode(),
                        c.GetEscapeCodeLength(),
                        &charsWritten,
                        nullptr
                ) || !WriteConsoleW(
                        hConsole,
                        &obj.data,
                        1,
                        &charsWritten,
                        nullptr
                ))
                {
                    std::cerr << "[Renderer] Error writing to console" << std::endl;
                    return;
                }
            }
        }

        ConsumeRenderBuffer();
    }


    void Renderer::InitRenderBuffer()
    {
        previousRenderBuffer = new RenderObject[bufferSize.X * bufferSize.Y];
        renderBuffer = new RenderObject[bufferSize.X * bufferSize.Y];
        zBufferIndex = new int[bufferSize.X * bufferSize.Y];
        updateBuffer = new bool[bufferSize.X * bufferSize.Y];

        for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i)
        {
            zBufferIndex[i] = 0;
        }
    }

    void Renderer::ConsumeRenderBuffer()
    {
        memcpy(previousRenderBuffer, renderBuffer, sizeof(RenderObject) * bufferSize.X * bufferSize.Y);

        for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i)
        {
            renderBuffer[i] = RenderObject();
            updateBuffer[i] = false;
            zBufferIndex[i] = -1;
        }
    }

    void Renderer::WriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color)
    {
        //todo crashes when going to far out of bounds. Guessing the error is somewhere here
        if (xy < 0 || xy > bufferSize.X * bufferSize.Y || zBufferIndex[xy] > z)
        {
            return;
        }

        //TODO smth is wrong herer
        /*if (!HasRenderObjectUpdated(xy))
        {
        }*/
            updateBuffer[xy] = true;
        ForceWriteRawIntoRenderBuffer(xy, z, data, color);
    }

    void Renderer::ForceWriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color)
    {
        renderBuffer[xy] = RenderObject{data, color};


        //return x + y * xDimension;

        zBufferIndex[xy] = data == ' ' ? z - 1000 : z;
    }


    void Renderer::WDrawSprite(Sprite* sprite, int originX, int originY, int z)
    {

        //todo might be able to be done in just one loop
        //todo fix if x is bigger than x dimension that it doesnt loop back one y lower
        for (int y = 0; y < sprite->textureDimensions->y; ++y)
        {
            for (int x = 0; x < sprite->textureDimensions->x; ++x)
            {
                int buffX = x + originX;
                int buffY = bufferSize.Y - originY - sprite->textureDimensions->y + y;


                //todo not super efficant
                if (buffX < 0 || buffY < 0 || buffX > bufferSize.X - 1 || buffY > bufferSize.Y - 1)
                {
                    continue;
                }

                WriteRawIntoRenderBuffer(
                        TranslateToBufferIndex(
                                buffX,
                                buffY,
                                bufferSize.X
                        ),
                        z,
                        //'a',
                        sprite->GetTexture()[y][x],
                        *(sprite->GetColor()[y][x])
                        //Color(255, 0, 0, false)
                );
            }
        }
    }

    void Renderer::WDrawText(const char* text, int originX, int originY, int z)
    {
        WDrawText(text, Color::WHT, originX, originY, z);
    }

    void Renderer::WDrawText(const char* text, Color color, int originX, int originY, int z)
    {
        for (int x = 0; x < strlen(text); ++x)
        {
            WriteRawIntoRenderBuffer(
                    TranslateToBufferIndex(
                            x + originX,
                            bufferSize.Y - originY - 1,
                            bufferSize.X
                    ),
                    z,
                    text[x],
                    color
            );
        }
    }

    void Renderer::Initialize()
    {
        InitRenderBuffer();
    }

    bool Renderer::HasRenderObjectUpdated(int xy)
    {
        return previousRenderBuffer[xy].data != renderBuffer[xy].data ||
               previousRenderBuffer[xy].color != renderBuffer[xy].color;
    }

    void Renderer::RenderThreat(int xStart, int yStart, int xEnd, int yEnd)
    {
        while(bRenderThreadActive) {
            //if()
        }
    }
} // Engine