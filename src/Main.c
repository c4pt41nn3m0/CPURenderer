#include<stdio.h>
#include "GlobalIncludes.h" 
#include "RenderLoop.h"

bool IsRunning = false;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

int WindowPosX = 0;
int WindowPosY = 0;
int WindowSizeX = 800;
int WindowSizeY = 600;

uint32_t* ColorBuffer = NULL;
SDL_Texture* ColorBufferTexture = NULL;


bool InitializeWindow(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error Initializing SDL \n");
		return false;
	}

	// Create SDL window
	WindowPosX = SDL_WINDOWPOS_CENTERED;
	WindowPosY = SDL_WINDOWPOS_CENTERED;
	Window = SDL_CreateWindow("Renderer", WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, SDL_WINDOW_BORDERLESS);

	if (!Window)
	{
		fprintf(stderr, "Error Creating SDL Window \n");
		return false;
	}
	
	// Create an SDL renderer 
	Renderer = SDL_CreateRenderer(Window, -1, 0);

	if (!Renderer)
	{
		fprintf(stderr, "Error Creating SDL Renderer \n");
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{

	// Initialization
	IsRunning = InitializeWindow();

	if (IsRunning)
	{
		printf("SDL Initialized");
	}

	// Setup and allocate resources
	Setup();

	// Lifecycle Loop
	while (IsRunning)
	{
		ProcessInput();
		Update();
		Draw();
	}

	// Destroy allocated resources
	Destroy();

	return 0;
}