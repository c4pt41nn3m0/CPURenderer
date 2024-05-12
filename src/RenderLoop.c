#include "GlobalIncludes.h"
#include "RenderLoop.h"

void setup(void)
{
	// TODO
}

void process_input(void)\
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			IsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			break;
	}
}

void update(void)
{
	// TODO
}

void draw(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//TODO render whatever we want

	SDL_RenderPresent(renderer);
}