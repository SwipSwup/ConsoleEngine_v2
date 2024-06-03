//
// Created by david on 01/06/2024.
//

#include <cmath>
#include "Vector3D.h"

namespace Engine
{
    Vector3D::Vector3D(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /*Vector3D Vector3D::operator=(Vector3D vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;

        return this;
    }*/

    Vector3D Vector3D::operator+(Vector3D vector)
    {
        return {this->x + vector.x, this->y + vector.y, this->z + vector.z};
    }

    Vector3D* Vector3D::operator+=(Vector3D vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        this->z += vector.z;

        return this;
    }

    bool Vector3D::operator==(Vector3D vector)
    {
        return this->x == vector.x && this->y == vector.y && this->z == vector.z;
    }

    Vector3D* Vector3D::operator*=(float num)
    {
        this->x *= num;
        this->y *= num;
        this->z *= num;

        return this;
    }

    Vector3D Vector3D::operator*(float num)
    {
        return {this->x * num, this->y * num, this->z * num};
    }
} // Engine