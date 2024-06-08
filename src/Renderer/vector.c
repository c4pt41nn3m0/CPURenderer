#include <math.h>
#include "vector.h"

///////////////////////////////////////////////////////////////////////////////
// Vector 2D functions
///////////////////////////////////////////////////////////////////////////////
float vec2_length(vec2_t v)
{
    return sqrt((v.x * v.x) + (v.y * v.y));
}

float vec2_length_squared(vec2_t v)
{
    return (v.x * v.x) + (v.y * v.y);
}

vec2_t vec2_add(vec2_t v1, vec2_t v2)
{
    vec2_t result = { 
        .x = (v1.x + v2.x), 
        .y = (v1.y + v2.y) };
    return result;
}

vec2_t vec2_sub(vec2_t v1, vec2_t v2)
{
    vec2_t result = { 
        .x = (v1.x - v2.x), 
        .y = (v1.y - v2.y) };
    return result;
}

vec2_t vec2_mul(vec2_t v, float factor)
{
    vec2_t result = { 
        .x = (v.x * factor), 
        .y = (v.y * factor) };
    return result;
}

vec2_t vec2_div(vec2_t v, float factor)
{
    vec2_t result = { 
        .x = (v.x / factor), 
        .y = (v.y / factor) };
    return result;
}

float vec2_dot(vec2_t v1, vec2_t v2)
{
    float dot = (v1.x * v2.x) + (v1.y * v2.y);

    return dot;
}

void vec2_normalize(vec2_t* v)
{
    if (v == NULL)
    {
        return;
    }

    float length = vec2_length(*v);
    
    if (length > 0)
    {
        v->x /= length;
        v->y /= length;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Vector 3D functions
///////////////////////////////////////////////////////////////////////////////
float vec3_length(vec3_t v)
{
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float vec3_length_squared(vec3_t v)
{
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

vec3_t vec3_add(vec3_t v1, vec3_t v2)
{
    vec3_t result = { 
        .x = (v1.x + v2.x), 
        .y = (v1.y + v2.y), 
        .z = (v1.z + v2.z) };
    return result;
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2)
{
    vec3_t result = { 
        .x = (v1.x - v2.x), 
        .y = (v1.y - v2.y), 
        .z = (v1.z - v2.z) };
    return result;
}

vec3_t vec3_mul(vec3_t v, float factor)
{
    vec3_t result = { 
        .x = (v.x * factor), 
        .y = (v.y * factor), 
        .z = (v.z * factor) };
    return result;
}

vec3_t vec3_div(vec3_t v, float factor)
{
    vec3_t result = {
        .x = (v.x / factor), 
        .y = (v.y / factor), 
        .z = (v.z / factor) };
    return result;
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2)
{
    vec3_t cross = {
        .x = (v1.y * v2.z) - (v1.z * v2.y),
        .y = (v1.z * v2.x) - (v1.x * v2.z),
        .z = (v1.x * v2.y) - (v1.y * v2.x)
    };
    return cross;
}

float vec3_dot(vec3_t v1, vec3_t v2)
{
    float dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

    return dot;
}

void vec3_normalize(vec3_t* v)
{
    if (v == NULL)
    {
        return;
    }

    float length = vec3_length(*v);

    if (length > 0)
    {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };
    return rotated_vector;
}
