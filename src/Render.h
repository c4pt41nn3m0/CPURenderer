#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

void ClearColorBuffer(uint32_t InClearColor);

void CreateColorBufferTexture(void);

void RenderColorBuffer(void);

void ToggleFullscreen(void);

void DrawRectangle(int PosX, int PosY, int SizeX, int SizeY, uint32_t InRectColor);

void DrawPixel(int X, int Y, uint32_t Color);

#endif