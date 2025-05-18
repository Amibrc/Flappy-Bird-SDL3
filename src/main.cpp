#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Game.hpp"


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	*appstate = new Game();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	Game* game = (Game*)appstate;
	game->Iter();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	Game* game = (Game*)appstate;

	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
	}

	game->EventHandler(event);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	Game* state = (Game*)appstate;
	delete state;
	SDL_Quit();
}
