//
// Created by david on 01/06/2024.
//

#include <cmath>
#include "Vector2D.h"

namespace Engine
{
    Vector2D Vector2D::zero = Vector2D(0, 0);

    Vector2D::Vector2D(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    double Vector2D::Distance(Vector2D vec)
    {
        return std::sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2));
    }
} // Engine