#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Game.h"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	*appstate = new Game();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	Game* game = (Game*)appstate;
	return game->Iter();
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	Game* game = (Game*)appstate;
	return game->EventHandler(event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	Game* game = (Game*)appstate;
	delete game;
}
