#include<stdio.h>
#include "GlobalIncludes.h" 
#include "RenderLoop.h"

bool IsRunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int WindowPosX = 0;
int WindowPosY = 0;
int WindowSizeX = 800;
int WindowSizeY = 600;


bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error Initializing SDL \n");
		return false;
	}

	// Create SDL window
	WindowPosX = SDL_WINDOWPOS_CENTERED;
	WindowPosY = SDL_WINDOWPOS_CENTERED;
	window = SDL_CreateWindow("Renderer", WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		fprintf(stderr, "Error Creating SDL Window \n");
		return false;
	}
	
	// Create an SDL renderer 
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		fprintf(stderr, "Error Creating SDL Renderer \n");
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{

	// Initialization
	IsRunning = initialize_window();

	if (IsRunning)
	{
		printf("SDL Initialized");
	}

	// Setup
	setup();

	// Lifecycle Loop
	while (IsRunning)
	{
		process_input();
		update();
		draw();
	}

	return 0;
}