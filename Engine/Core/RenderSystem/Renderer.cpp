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

    RenderObject::RenderObject(wchar_t data, Color color): color(color)
    {
        this->data = data;
    }

    int Renderer::TranslateToBufferIndex(int x, int y, int xDimension)
    {
        return x + y * xDimension;
    }

    bool Renderer::HasRenderObjectUpdated(int xy)
    {
        return previousRenderBuffer[xy].data != renderBuffer[xy].data ||
               previousRenderBuffer[xy].color != renderBuffer[xy].color;
    }

    void Renderer::Render()
    {
        DWORD charsWritten;

        for (int y = 0; y < bufferSize.Y; ++y)
        {
            for (int x = 0; x < bufferSize.X; ++x)
            {
                int bufferIndex = TranslateToBufferIndex(x, y, bufferSize.X);
                RenderObject obj = renderBuffer[bufferIndex];

                Color c = obj.color;

                /*if (!HasRenderObjectUpdated(bufferIndex))
                {
                    if (bHighlightUnchangedPositions)
                    {
                        c = Color::GRNHB;
                    }
                    else
                    {
                        continue;
                    }
                }*/

                SetConsoleCursorPosition(hConsole, COORD{(SHORT)x, (SHORT)y});
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
                    std::cerr << "Error writing to console" << std::endl;
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

        for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i)
        {
            zBufferIndex[i] = 0;
        }
    }

    void Renderer::ConsumeRenderBuffer()
    {
        memcpy(previousRenderBuffer, renderBuffer, sizeof(RenderObject) * bufferSize.X * bufferSize.Y);

        delete[] renderBuffer;
        renderBuffer = new RenderObject[bufferSize.X * bufferSize.Y];

        for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i)
        {
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

        ForceWriteRawIntoRenderBuffer(xy, z, data, color);
    }

    void Renderer::ForceWriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color)
    {
        renderBuffer[xy] = RenderObject{data, color};

        zBufferIndex[xy] = z;
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
                if(buffX < 0 || buffY < 0 || buffX > bufferSize.X - 1 || buffY > bufferSize.Y - 1)
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
                        sprite->texture[y][x],
                        sprite->color[y][x]
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
} // Engine