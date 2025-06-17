#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(SDL_Renderer* renderer,
										float x, float y,
										const char* const files[], size_t count,
										Uint64 frameDuration,
										bool isPosCenter)
	: currentTextureIndex(0), lastTicks(0), frameDuration(frameDuration)
{
	int validTextureIndex = -1;

	textures.reserve(count);
	for (size_t i = 0; i < count; i++)
	{
		textures.push_back(IMG_LoadTexture(renderer, files[i]));
		if (!textures[i])
			SDL_Log("Failed to load texture [%s]", SDL_GetError());
		else
			validTextureIndex = i;
	}

	if (validTextureIndex > -1)
		if (isPosCenter)
			rect = { x - textures[validTextureIndex]->w / 2.0f,
					y - textures[validTextureIndex]->h / 2.0f,
					(float)textures[validTextureIndex]->w,
					(float)textures[validTextureIndex]->h };
		else
			rect = { x, y, (float)textures[validTextureIndex]->w, (float)textures[validTextureIndex]->h };
	else
		rect = { x, y, 0, 0 };
}

AnimatedGameObject::~AnimatedGameObject()
{
	for (auto& texture : textures)
		SDL_DestroyTexture(texture);
}

void AnimatedGameObject::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, textures[currentTextureIndex], nullptr, &rect);
}

void AnimatedGameObject::Update()
{
	Uint64 nowTicks = SDL_GetTicks();
	if (nowTicks - lastTicks >= frameDuration)
	{
		++currentTextureIndex %= textures.size();
		lastTicks = nowTicks;
	}
}

bool AnimatedGameObject::HasTextures() const
{
	for (const auto& texture : textures)
		if (texture == nullptr)
			return false;
	return true;
}
