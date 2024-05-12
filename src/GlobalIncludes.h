#ifndef GLOBAL_INCLUDES_H
#define GLOBAL_INCLUDES_H

#include <stdbool.h>
#include <SDL.h>

extern bool IsRunning;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int WindowPosX;
extern int WindowPosY;
extern int WindowSizeX;
extern int WindowSizeY;

#endif // GLOBAL_INCLUDES_H