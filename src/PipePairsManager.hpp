#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <memory>

#include "PipePair.hpp"
#include "Config.hpp"

class PipePairsManager
{
public:
	PipePairsManager(SDL_Renderer* renderer);

	void RenderDraw(SDL_Renderer* renderer) const;
	void Update();
	void Reset();

	bool CheckCollisionWithPipePairs(const SDL_FRect* rect) const;

private:
	std::array<std::unique_ptr<PipePair>, PIPE_PAIRS_COUNT> pipePairs;
};

