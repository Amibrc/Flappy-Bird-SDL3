#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>

#include "Score.h"
#include "Config.h"

Score::Score(SDL_Renderer* renderer)
	: NumberDisplay(".png"), _score(0)
{
	UpdateTexture(renderer);
	rect.y = 80.0f;
	rect.h = digitH;
}

Score::~Score()
{
	SDL_DestroyTexture(texture);
}

void Score::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

void Score::Increment(SDL_Renderer* renderer)
{
	++_score;
	UpdateTexture(renderer);
}

void Score::Reset(SDL_Renderer* renderer)
{
	_score = 0;
	UpdateTexture(renderer);
}

void Score::UpdateTexture(SDL_Renderer* renderer)
{
	if (texture)
		SDL_DestroyTexture(texture);

	SDL_Surface* surface = NumberDisplay::CreateNumberSurface(_score);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	if (!texture)
		SDL_Log("Error to create texture from surface [%s]", SDL_GetError());
	else
	{
		rect.x = WINDOW_CENTER_X - texture->w / 2.0f;
		rect.w = (float)texture->w;
	}
}
