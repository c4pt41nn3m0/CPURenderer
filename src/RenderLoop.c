#include "RenderLoop.h"
#include "Render.h"
#include "Display.h"
#include "Vector.h"

void Setup(void)
{
	// Allocate Color Buffer Memory
	ColorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * WindowSizeX * WindowSizeY);
	
	// Initialize SDL_Texture 
	CreateColorBufferTexture();

	// Populate array of vector points for display
	/*
	for (float x = -1; x <= 1; x += 0.25)
	{
		for (float y = -1; y <= 1; y += 0.25)
		{
			for (float z = -1; z <= 1; z += 0.25)
			{
				vec3_t NewPoint = { x, y, z };
			}
		}
	}
	*/
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

void Render(void)
{


	// Copy ColorBuffer to SDL_Texture
	RenderColorBuffer();

	// Clear our color buffer to color
	ClearColorBuffer(0x00000000);

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