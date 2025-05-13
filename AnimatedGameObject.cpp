#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "AnimatedGameObject.hpp"

AnimatedGameObject::AnimatedGameObject(SDL_Renderer* renderer,
										float x, float y,
										const char* const files[], size_t count,
										Uint64 frameDuration)
	: currentTextureIndex(0), lastTicks(0), frameDuration(frameDuration)
{
	textures.reserve(count);
	for (size_t i = 0; i < count; i++)
	{
		textures.push_back(IMG_LoadTexture(renderer, files[i]));
		if (!textures[i])
		{
			SDL_Log("Error: IMG_LoadTexture - %s", SDL_GetError());
			rect = { x, y, 0, 0 };
			return;
		}
	}

	rect = { x, y, (float)textures[currentTextureIndex]->w, (float)textures[currentTextureIndex]->h };
}

AnimatedGameObject::~AnimatedGameObject()
{
	for (auto& texture : textures)
		SDL_DestroyTexture(texture);
}

void AnimatedGameObject::RenderDraw(SDL_Renderer* renderer) const
{ SDL_RenderTexture(renderer, textures[currentTextureIndex], nullptr, &rect); }

void AnimatedGameObject::Update()
{
	Uint64 nowTicks = SDL_GetTicks();
	if (nowTicks - lastTicks > frameDuration)
	{
		++currentTextureIndex %= textures.size();
		lastTicks = nowTicks;
	}
}
