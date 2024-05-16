#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

extern void ClearColorBuffer(uint32_t InClearColor);

extern void CreateColorBufferTexture(void);

extern void RenderColorBuffer(void);

extern void ToggleFullscreen(void);

extern void DrawGrid(uint32_t InGridColor);

extern void DrawRectangle(int PosX, int PosY, int SizeX, int SizeY, uint32_t InRectColor);

#endif