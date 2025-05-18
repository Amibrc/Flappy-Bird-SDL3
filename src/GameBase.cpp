#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "GameBase.hpp"
#include "Config.hpp"

GameBase::GameBase()
{
	SDL_srand(SDL_GetPerformanceCounter());

	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Log("Error: SDL_Init - %s\n", SDL_GetError());

	if (!SDL_CreateWindowAndRenderer("Flappy Bird", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
		SDL_Log("Error: SDL_CreateWindowAndRenderer - %s\n", SDL_GetError());

	if (!SDL_SetWindowIcon(window, IMG_Load(iconTextureFile)))
		SDL_Log("Error: SDL_SetWindowIcon - %s\n", SDL_GetError());
}

GameBase::~GameBase()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}