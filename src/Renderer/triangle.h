#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

typedef struct {
	int a; // 1st face index
	int b; // 2nd face index
	int c; // 3rd face index
} face_t;

typedef struct {
	vec2_t points[3];
} triangle_t;

#endif
