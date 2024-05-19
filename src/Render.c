#include "Render.h"
#include "Display.h"

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

void DrawRectangle(int PosX, int PosY, int SizeX, int SizeY, uint32_t InRectColor)
{
	
	for (int y = PosY; y < WindowSizeY; y++)
	{
		if (y < (PosY + SizeY))
		{
			for (int x = PosX; x < WindowSizeX; x++)
			{
				if (x < (PosX + SizeX))
				{
					DrawPixel(x, y, InRectColor);
				}

				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
}

void DrawPixel(int PosX, int PosY, uint32_t Color)
{
	if ((PosX < 0) || (PosY < 0) ||(PosX > WindowSizeX - 1) || (PosY > WindowSizeY - 1))
	{
		return;
	}

	ColorBuffer[(WindowSizeX * PosY) + PosX] = Color;
}

vec2_t OrthoProject(vec3_t Point)
{
	vec2_t ProjectedPoint = {FOVFactor * Point.x, FOVFactor * Point.y};

	return ProjectedPoint;
}

vec2_t PerspectiveProject(vec3_t Point)
{
	vec2_t ProjectedPoint = { FOVFactor * Point.x / Point.z, FOVFactor * Point.y / Point.z};

	return ProjectedPoint;
}
