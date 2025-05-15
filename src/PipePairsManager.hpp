#pragma once

#include <SDL3/SDL.h>

#include "PipePair.hpp"

class PipePairsManager
{
public:
	PipePair* pipePairs[3];

	PipePairsManager(SDL_Renderer* renderer);

	~PipePairsManager();

	void RenderDraw(SDL_Renderer* renderer) const;

	void Update();

	bool CheckCollisionWithPipePairs(const SDL_FRect* rect) const;

	void Reset();
};

