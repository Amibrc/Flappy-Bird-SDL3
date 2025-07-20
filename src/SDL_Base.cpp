#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SDL_Base.h"
#include "Config.h"

SDL_Base::SDL_Base()
{
	SDL_srand(SDL_GetPerformanceCounter());

	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Log("Error to init SDL [%s]", SDL_GetError());
	
	window = SDL_CreateWindow("Flappy Bird", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
	if (!window)
		SDL_Log("Error to create window [%s]", SDL_GetError());

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
		SDL_Log("Error to create renderer [%s]", SDL_GetError());

	SDL_Surface* iconSurface = IMG_Load(iconFile);
	if (!iconSurface)
		SDL_Log("Failed to load icon [%s]", SDL_GetError());
	else
	{
		if (!SDL_SetWindowIcon(window, iconSurface))
			SDL_Log("Error setting icon [%s]", SDL_GetError());
		SDL_DestroySurface(iconSurface);
	}
}

SDL_Base::~SDL_Base()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}