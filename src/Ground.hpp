#pragma once

#include <SDL3/SDL.h>

#include "GameObject.hpp"

class Ground
{
public:
	Ground(SDL_Renderer* renderer);

	~Ground();
	
	void RenderDraw(SDL_Renderer* renderer);

	void Update();

private:
	GameObject* groundPieces[2];
};

