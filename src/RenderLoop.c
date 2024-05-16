#include "RenderLoop.h"
#include "Render.h"
#include "Display.h"

void Setup(void)
{
	// Allocate Color Buffer Memory
	ColorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * WindowSizeX * WindowSizeY);
	
	// Initialize SDL_Texture 
	CreateColorBufferTexture();
}

void ProcessInput(void)
{
	// Poll SDL events
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		// Close button clicked
		case SDL_QUIT:
			IsRunning = false;
			break;
		// Escape key pressed
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			if (event.key.keysym.sym == SDLK_F11)
			{
				ToggleFullscreen();
			}
			break;
	}
}

void Update(void)
{
	// TODO
}

void Draw(void)
{
	// Render clear color
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);

	DrawGrid(0x00000000);
	DrawRectangle(100, 100, 640, 480, 0xFFFF0000);

	// Copy ColorBuffer to SDL_Texture
	RenderColorBuffer();

	// Clear our color buffer to input color
	ClearColorBuffer(0xFFFFFFFF);

	// Send data to SDL backbuffer
	SDL_RenderPresent(Renderer);
}

void Destroy(void)
{
	free(ColorBuffer);

	SDL_DestroyTexture(ColorBufferTexture);
	
	SDL_DestroyRenderer(Renderer);
	
	SDL_DestroyWindow(Window);
	
	SDL_Quit();
}