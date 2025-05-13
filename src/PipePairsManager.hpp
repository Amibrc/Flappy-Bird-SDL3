#pragma once

#include <SDL3/SDL.h>

#include "PipePair.hpp"

class PipePairsManager
{
public:
	PipePair* pipePairs[3];
	float distance;

	PipePairsManager(SDL_Renderer* renderer, float distance);

	~PipePairsManager();

	void RenderDraw(SDL_Renderer* renderer) const;

	void Update();

	bool CheckCollisionWithPipePairs(const SDL_FRect* rect) const;

	void Reset();
};

