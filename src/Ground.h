#pragma once

#include <SDL3/SDL.h>

#include <vector>
#include <memory>

#include "GameObject.h"

class Ground
{
public:
	Ground(SDL_Renderer* renderer);
	~Ground() = default;
	
	void RenderDraw(SDL_Renderer* renderer);
	void Update();

private:
	std::vector<std::unique_ptr<GameObject>> groundPieces;
};

