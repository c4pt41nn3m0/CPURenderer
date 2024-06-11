#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

// Configuration types
extern bool fullscreen;
enum projection_type {
	PROJECTION_ORTHO = 0,
	PROJECTION_PERSPECTIVE = 1
} projection_type;
enum cull_type {
	CULL_NONE = 0,
	CULL_BACKFACE
} culling_type;
enum render_method {
	RENDER_WIRE = 0,
	RENDER_WIRE_VERTEX = 1,
	RENDER_FILL_TRIANGLE = 2,
	RENDER_FILL_TRIANGLE_WIRE = 3
} render_method;

bool initialize_window(void);
void draw_grid(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);
void toggle_fullscreen(void);
void toggle_projection(void);
void toggle_backface_culling(void);
void cycle_render_method(void);

#endif
