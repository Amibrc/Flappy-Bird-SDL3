#pragma once

#include <SDL3/SDL.h>

#include <array>

#include "GameObjectBase.h"
#include "NumberDisplay.h"

class Stats : public GameObjectBase, public NumberDisplay
{
public:
	Stats(SDL_Renderer* renderer);
	~Stats();

	void RenderDraw(SDL_Renderer* renderer) const override;
	void Update(SDL_Renderer* renderer, size_t score);

private:
	SDL_Texture* texture;
	SDL_Surface* bannerSurface;
	std::array<SDL_Surface*, 4> medalSurfaces;
	size_t cachedScore;
	size_t bestScore;

	void RenderBanner(SDL_Surface* target);
	void RenderNumber(SDL_Surface* target, size_t number, int y);
	void RenderMedal(SDL_Surface* target, size_t score);
};

