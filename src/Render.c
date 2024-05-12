#include "GlobalIncludes.h"
#include "Render.h"

void ClearColorBuffer(uint32_t InClearColor)
{
	for (int y = 0; y < WindowSizeY; y++)
	{
		for (int x = 0; x < WindowSizeX; x++)
		{
			ColorBuffer[(WindowSizeX * y) + x] = InClearColor;
		}
	}
	
}

void CreateColorBufferTexture()
{
	ColorBufferTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowSizeX, WindowSizeY);
}

void RenderColorBuffer()
{
	SDL_UpdateTexture(ColorBufferTexture, NULL, ColorBuffer, (int)(WindowSizeX * sizeof(uint32_t)));
	SDL_RenderCopy(Renderer, ColorBufferTexture, NULL, NULL);
}
