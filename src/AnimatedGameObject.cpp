#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(SDL_Renderer* renderer,
										float x, float y,
										const char* const files[], size_t count,
										Uint64 frameDuration, bool isPosCenter)
	: currentTextureIndex(0), lastTicks(0), frameDuration(frameDuration)
{
	textures.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		textures.push_back(IMG_LoadTexture(renderer, files[i]));
		if (!textures[i])
			SDL_Log("Failed to load texture [%s]", SDL_GetError());
	}

	for (auto& tex : textures)
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

AnimatedGameObject::~AnimatedGameObject()
{
	for (auto& tex : textures)
		SDL_DestroyTexture(tex);
}

void AnimatedGameObject::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, textures[currentTextureIndex], nullptr, &rect);
}

void AnimatedGameObject::Update(Uint64 nowTicks)
{
	if (nowTicks - lastTicks >= frameDuration)
	{
		++currentTextureIndex %= textures.size();
		lastTicks = nowTicks;
	}
}

bool AnimatedGameObject::HasTextures() const
{
	for (const auto& tex : textures)
		if (tex == nullptr)
			return false;
	return true;
}
