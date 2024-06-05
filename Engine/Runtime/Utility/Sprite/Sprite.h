//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_SPRITE_H
#define CONSOLEENGINE_V2_SPRITE_H

namespace Engine
{

        struct Color;
        struct Vector2D;

        struct Sprite
        {
        public:
            Sprite();
            Sprite(wchar_t** texture, Vector2D textureDimensions);
            Sprite(wchar_t** texture, Color** color, Vector2D textureDimensions);
            ~Sprite();

            Vector2D* textureDimensions;
            wchar_t** texture;
            Color** color;

        private:
            void Init(wchar_t** texture, Color** color, Vector2D textureDimensions);

        public:
            void Load2DTexture(wchar_t** texture);

            void Load2DColor(Color** color);

            void Load2DTextureAndColor(wchar_t** texture, Color** color);

            void Load2DTextureFromFile(char* path);
            void Load2DColorFromFile(char* path);
        private:
    };

} // Engine

#endif //CONSOLEENGINE_V2_SPRITE_H
