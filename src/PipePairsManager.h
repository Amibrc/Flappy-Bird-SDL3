#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <memory>

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
	bool IsPassedBy(float targetX) const;

private:
	std::array<std::unique_ptr<PipePair>, PIPE_PAIRS_COUNT> pipePairs;
};

