#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

extern bool IsRunning;

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

extern int WindowPosX;
extern int WindowPosY;
extern int WindowSizeX;
extern int WindowSizeY;
extern bool Fullscreen;
extern float FOVFactor;

extern uint32_t* ColorBuffer;
extern SDL_Texture* ColorBufferTexture;

#endif // GLOBAL_INCLUDES_H