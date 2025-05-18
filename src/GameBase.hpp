#pragma once

class GameBase
{
public:
	GameBase();
	~GameBase();

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

