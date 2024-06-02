//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_VECTOR2D_H
#define CONSOLEENGINE_V2_VECTOR2D_H

namespace Engine
{

    struct Vector2D
    {
    public:
        Vector2D() = default;

        Vector2D(int x, int y);

        int x, y;

        double Distance(Vector2D vec);

        static Vector2D zero;
    };

} // Engine

#endif //CONSOLEENGINE_V2_VECTOR2D_H
