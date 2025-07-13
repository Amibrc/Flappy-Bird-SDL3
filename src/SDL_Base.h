#pragma once

class SDL_Base
{
public:
	SDL_Base();
	virtual ~SDL_Base();

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

