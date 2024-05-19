#pragma once

#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	double x;
	double y;

}vec2_t;

typedef struct
{
	double x;
	double y;
	double z;

}vec3_t;

// TODO Declare operations with vectors

// Rotation Functions

vec3_t Vec3_Rotate_X(vec3_t V, double Angle);
vec3_t Vec3_Rotate_Y(vec3_t V, double Angle);
vec3_t Vec3_Rotate_Z(vec3_t V, double Angle);

#endif