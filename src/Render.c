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

void CreateColorBufferTexture(void)
{
	ColorBufferTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowSizeX, WindowSizeY);
}

void RenderColorBuffer(void)
{
	SDL_UpdateTexture(ColorBufferTexture, NULL, ColorBuffer, (int)(WindowSizeX * sizeof(uint32_t)));
	SDL_RenderCopy(Renderer, ColorBufferTexture, NULL, NULL);
}

void ToggleFullscreen(void)
{
	if (Fullscreen == false)
	{
		Fullscreen = true;
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		Fullscreen = false;
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_MAXIMIZED);
	}
}

void DrawGrid(uint32_t InGridColor)
{
	for (int y = 0; y < WindowSizeY; y++)
	{
		for (int x = 0; x < WindowSizeX; x++)
		{
			if (y % 10 == 0)
			{
				ColorBuffer[(WindowSizeX * y) + x] = InGridColor;
			}
			if (x % 10 == 0)
			{
				ColorBuffer[(WindowSizeX * y) + x] = InGridColor;
			}
		}
	}
}

void DrawRectangle(int PosX, int PosY, int SizeX, int SizeY, uint32_t InRectColor)
{
	if ((PosX > WindowSizeX) || (PosY > WindowSizeY))
	{
		return;
	}

	
	for (int y = PosY; y < WindowSizeY; y++)
	{
		for (int x = PosX; x < WindowSizeX; x++)
		{
			if (y < (PosY + SizeY) && x < (PosX + SizeX))
			{
				ColorBuffer[(WindowSizeX * y) + x] = InRectColor;
			}
		}
	}
}
