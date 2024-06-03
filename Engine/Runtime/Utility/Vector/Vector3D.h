//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_VECTOR3D_H
#define CONSOLEENGINE_V2_VECTOR3D_H

namespace Engine
{

    struct Vector3D
    {
        Vector3D(float x, float y, float z);

        float x, y, z;

        //Vector3D operator =(Vector3D);

        Vector3D operator+(Vector3D vector);
        Vector3D operator*(float num);

        Vector3D* operator*=(float num);

        Vector3D* operator+=(Vector3D vector);

        bool operator==(Vector3D vector);
    };

} // Engine

#endif //CONSOLEENGINE_V2_VECTOR3D_H
