#include "Vector.h"
#include <math.h>

// TODO Implement operations with vectors

// Rotation Functions

vec3_t Vec3_Rotate_X(vec3_t V, double Angle)
{
    vec3_t RotatedVector = {
        V.x,
        (V.y * cos(Angle)) - (V.z * sin(Angle)),
        (V.y * sin(Angle)) + (V.z * cos(Angle))
    };

    return RotatedVector;
}

vec3_t Vec3_Rotate_Y(vec3_t V, double Angle)
{
    vec3_t RotatedVector = {
        (V.x * cos(Angle)) - (V.z * sin(Angle)),
        V.y,
        (V.x * sin(Angle)) + (V.z * cos(Angle))
    };

    return RotatedVector;
}

vec3_t Vec3_Rotate_Z(vec3_t V, double Angle)
{
    vec3_t RotatedVector = {
        (V.x * cos(Angle)) - (V.y * sin(Angle)),
        (V.x * sin(Angle)) + (V.y * cos(Angle)),
        V.z
    };

    return RotatedVector;
}
