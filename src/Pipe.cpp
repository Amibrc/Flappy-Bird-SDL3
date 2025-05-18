#include <SDL3/SDL.h>

#include "Pipe.hpp"
#include "Config.hpp"

Pipe::Pipe(SDL_Renderer* renderer, float x, float y, bool flipped)
	: GameObject(renderer, x, y, pipeGreenTextureFile, false), flipped(flipped) {}

void Pipe::RenderDraw(SDL_Renderer* renderer) const
{
	if (flipped)
		SDL_RenderTextureRotated(renderer, texture, nullptr, &rect, 0, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
