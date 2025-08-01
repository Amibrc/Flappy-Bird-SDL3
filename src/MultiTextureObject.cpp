#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "MultiTextureObject.h"

MultiTextureObject::MultiTextureObject(SDL_Renderer* renderer, float x, float y, const char* const files[], size_t count, bool isPosCenter)
	: currentTextureIndex(0)
{
	textures.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		textures.push_back(IMG_LoadTexture(renderer, files[i]));
		if (!textures[i])
			SDL_Log("Failed to load texture [%s]", SDL_GetError());
	}

	for (const auto& tex : textures)
	{
		if (tex)
		{
			if (isPosCenter)
				rect = { x - tex->w / 2.0f, y - tex->h / 2.0f, (float)tex->w, (float)tex->h };
			else
				rect = { x, y, (float)tex->w, (float)tex->h };
			return;
		}
	}

	rect = { x, y, 0, 0 };
}

MultiTextureObject::~MultiTextureObject()
{
	for (auto& tex : textures)
		SDL_DestroyTexture(tex);
}

void MultiTextureObject::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, textures[currentTextureIndex], nullptr, &rect);
}

void MultiTextureObject::Switch()
{
	currentTextureIndex = (currentTextureIndex + 1) % textures.size();
}
