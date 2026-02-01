#include <SDL3\SDL.h>
#include <SDL3_image/SDL_image.h>

#include <array>
#include <string>

#include "TextureManager.h"

#include "Stats.h"
#include "Config.h"

Stats::Stats(SDL_Renderer* renderer)
	: NumberDisplay("-1.png"), statsBannerSurface(TextureManager::GetSurface(STATS_BANNER_FILE)),
	newBannerSurface(TextureManager::GetSurface(NEW_BANNER_FILE)), texture(nullptr),
	cachedScore(SIZE_MAX), bestScore(0)
{
	if (!statsBannerSurface)
		rect = { WINDOW_CENTER_X, 300.0f, 0, 0 };
	else
		rect = { WINDOW_CENTER_X - statsBannerSurface->w / 2.0f, 300.0f, (float)statsBannerSurface->w, (float)statsBannerSurface->h };

	for (int i = 0; i < 4; ++i)
		medalSurfaces[i] = TextureManager::GetSurface(MEDAL_FILES[i]);
}

void Stats::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

void Stats::Update(SDL_Renderer* renderer, size_t score)
{
	if (score == cachedScore)
		return;

	if (texture)
		SDL_DestroyTexture(texture);

	cachedScore = score;
	SDL_Surface* surface = SDL_CreateSurface(rect.w, rect.h, SDL_PIXELFORMAT_ABGR32);

	if (!surface)
	{
		SDL_Log("Error to create surface [%s]", SDL_GetError());
		if (score > bestScore)
			bestScore = score;
		return;
	}

	RenderStatsBanner(surface);

	if (score > bestScore)
	{
		bestScore = score;
		RenderNewBanner(surface);
	}

	RenderMedal(surface, score);
	RenderNumber(surface, score, 70);
	RenderNumber(surface, bestScore, 150);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
}

void Stats::RenderStatsBanner(SDL_Surface* target)
{
	SDL_Rect dstrect = { 0, 0, 0, 0 };
	SDL_BlitSurface(statsBannerSurface, nullptr, target, &dstrect);
}

void Stats::RenderNewBanner(SDL_Surface* target)
{
	SDL_Rect dstrect = { 280, 120, 0, 0 };
	SDL_BlitSurface(newBannerSurface, nullptr, target, &dstrect);
}

void Stats::RenderNumber(SDL_Surface* target, size_t number, int y)
{
	SDL_Surface* numberSurface = CreateNumberSurface(number);
	SDL_Rect dstrect = { 420 - numberSurface->w, y, 0, 0 };
	SDL_BlitSurface(numberSurface, nullptr, target, &dstrect);
	SDL_DestroySurface(numberSurface);
}

void Stats::RenderMedal(SDL_Surface* target, size_t score)
{
	int medalIndex = -1;
	if (score >= SCORE_MEDAL_GOLD)
		medalIndex = 3;
	else if (score >= SCORE_MEDAL_PLATINUM)
		medalIndex = 2;
	else if (score >= SCORE_MEDAL_SILVER)
		medalIndex = 1;
	else if (score >= SCORE_MEDAL_BRONZE)
		medalIndex = 0;

	if (medalIndex != -1 && medalSurfaces[medalIndex])
	{
		SDL_Rect dstrect = { 65, 90, 0, 0 };
		SDL_BlitSurface(medalSurfaces[medalIndex], nullptr, target, &dstrect);
	}
}
