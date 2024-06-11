#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "stdint.h"

typedef struct {
	int a; // 1st face index
	int b; // 2nd face index
	int c; // 3rd face index
	uint32_t color; // face color
} face_t;

typedef struct  {
	vec2_t points[3];
	uint32_t color;
	float avg_depth;
} triangle_t;

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);


#endif
