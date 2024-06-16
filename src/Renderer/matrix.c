#include "matrix.h"
#include "math.h"

mat4_t mat4_identity(void)
{
    mat4_t identity = { {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
        } };

    return identity;
}

mat4_t mat4_make_scale(float sx, float sy, float sz)
{
    mat4_t scale = mat4_identity();
    scale.m[0][0] = sx;
    scale.m[1][1] = sy;
    scale.m[2][2] = sz;

    return scale;
}

mat4_t mat4_make_translation(float tx, float ty, float tz)
{
    mat4_t translate = mat4_identity();
    translate.m[0][3] = tx;
    translate.m[1][3] = ty;
    translate.m[2][3] = tz;

    return translate;
}

mat4_t mat4_make_rotation_x(float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    mat4_t rot_x = mat4_identity();
    rot_x.m[1][1] = c;
    rot_x.m[1][2] = -s;
    rot_x.m[2][1] = s;
    rot_x.m[2][2] = c;

    return rot_x;
}

mat4_t mat4_make_rotation_y(float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    mat4_t rot_y = mat4_identity();
    rot_y.m[0][0] = c;
    rot_y.m[0][2] = s;
    rot_y.m[2][0] = -s;
    rot_y.m[2][2] = c;

    return rot_y;
}

mat4_t mat4_make_rotation_z(float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    mat4_t rot_z = mat4_identity();
    rot_z.m[0][0] = c;
    rot_z.m[0][1] = -s;
    rot_z.m[1][0] = s;
    rot_z.m[1][1] = c;

    return rot_z;
}

vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
    
    vec4_t v4;

    v4.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    v4.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    v4.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    v4.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

    return v4;
}
