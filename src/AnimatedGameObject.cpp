#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(SDL_Renderer* renderer,
										float x, float y,
										const char* const files[], size_t count,
										bool isPosCenter, Uint64 frameDuration)
	: MultiTextureObject(renderer, x, y, files, count, isPosCenter),
	frameDuration(frameDuration), lastTicks(SDL_GetTicks()) {}

void AnimatedGameObject::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, textures[currentTextureIndex], nullptr, &rect);
}

void AnimatedGameObject::Update(Uint64 nowTicks)
{
	if (nowTicks - lastTicks >= frameDuration)
	{
		Switch();
		lastTicks = nowTicks;
	}
}