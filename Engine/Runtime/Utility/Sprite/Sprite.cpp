//
// Created by david on 01/06/2024.
//

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "Sprite.h"
#include "External/lodepng/lodepng.h"
#include "../Vector/Vector2D.h"
#include "../Color/Color.h"

namespace Engine
{
    Sprite::Sprite()
    {

    }

    Sprite::Sprite(wchar_t** texture, Vector2D textureDimensions)
    {
        Init(texture, nullptr, textureDimensions);
    }

    Sprite::Sprite(wchar_t** texture, Color** color, Vector2D textureDimensions)
    {
        Init(texture, color, textureDimensions);
    }

    Sprite::~Sprite()
    {
        delete textureDimensions;

        for (int y = 0; y < textureDimensions->y; ++y)
        {
            delete[] texture[y];
            delete[] color[y];
        }

        delete[] texture;
        delete[] color;
    }

    void Sprite::Init(wchar_t** texture, Color** color, Vector2D textureDimensions)
    {
        this->textureDimensions = new Vector2D(textureDimensions);

        Load2DTexture(texture);
        Load2DColor(color);
    }

    void Sprite::Load2DTexture(wchar_t** texture)
    {
        if (texture == nullptr)
        {
            this->texture = new wchar_t* [textureDimensions->y];
            for (int y = 0; y < textureDimensions->y; ++y)
            {
                this->texture[y] = new wchar_t[textureDimensions->x];
                for (int x = 0; x < textureDimensions->x; ++x)
                {
                    this->texture[y][x] = ' ';
                }
            }
        }
        else
        {
            this->texture = texture;
        }
    }

    void Sprite::Load2DColor(Color** color)
    {
        if (color == nullptr)
        {
            this->color = new Color* [textureDimensions->y];
            for (int y = 0; y < textureDimensions->y; ++y)
            {
                this->color[y] = new Color[textureDimensions->x];
                for (int x = 0; x < textureDimensions->x; ++x)
                {
                    this->color[y][x] = Color::WHT;
                }
            }
        }
        else
        {
            this->color = color;
        }
    }

    void Sprite::Load2DTextureAndColor(wchar_t** texture, Color** color)
    {
        Load2DTexture(texture);
        Load2DColor(color);
    }

    void Sprite::Load2DTextureFromFile(char* path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::cerr << "[Sprite] Error opening file " << path << std::endl;
            return;
        }

        std::vector<std::vector<wchar_t>*> textureList;
        std::string line;

        int maxVerticalDimension = 0;

        while (getline(file, line))
        {
            std::vector<wchar_t>* charList = new std::vector<wchar_t>();
            for (const char &item: line)
            {
                charList->push_back((wchar_t) item);
            }
            textureList.push_back(charList);

            if(charList->size() > maxVerticalDimension)
                maxVerticalDimension = charList->size();
        }

        file.close();

        wchar_t ** textureArray = new wchar_t*[textureList.size()];

        for (int i = 0; i < textureList.size(); ++i)
        {
            textureArray[i] = new wchar_t [maxVerticalDimension];

            if(textureList[i]->size() != maxVerticalDimension) {
                for (int j = textureList[i]->size(); j < maxVerticalDimension; ++j)
                {
                    textureList[i]->push_back(' ');
                }
            }

            wchar_t* charArray = new wchar_t [textureList[i]->size()];
            std::copy(textureList[i]->begin(), textureList[i]->end(), charArray);
            textureArray[i] = charArray;

            delete textureList[i];
        }

        texture = textureArray;
        textureDimensions = new Vector2D(maxVerticalDimension, textureList.size());
    }

    void Sprite::Load2DColorFromFile(char* path)
    {
        std::vector<unsigned char> image; //the raw pixels
        unsigned width, height;

        //decode
        unsigned error = lodepng::decode(image, width, height, path);

        //if there's an error, display it
        if(error) {
            std::cout << "[Texture] decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            return;
        }

        if(width != textureDimensions->x || height != textureDimensions->y) {
            std::cerr << "[Texture] Color file has incorrect dimensions" << std::endl;
            return;
        }   

        Color** colorArray = new Color*[textureDimensions->y];

        for (int i = 0; i < textureDimensions->y; ++i)
        {
            colorArray[i] = new Color[textureDimensions->x];

            for (int j = 0; j < textureDimensions->x; ++j)
            {
                std::cout << image[textureDimensions->y * i + j] << std::endl;
            }
        }
    }


} // Engine