#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "PipePair.h"
#include "Config.h"

class PipePairsManager
{
public:
	PipePairsManager(SDL_Renderer* renderer);
	~PipePairsManager() = default;

	void RenderDraw(SDL_Renderer* renderer) const;
	void Update(float deltaTime);
	void Reset();

	bool CheckCollisionWithPipePairs(const SDL_FRect* rect) const;
	bool IsPassedBy(float targetX);

private:
	std::vector<PipePair> pipePairs;
};

