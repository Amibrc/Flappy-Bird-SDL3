#pragma once

class GameBase
{
public:
	GameBase();
	virtual ~GameBase();

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

