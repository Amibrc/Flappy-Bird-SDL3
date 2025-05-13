#pragma once

#include <SDL3/SDL.h>

#include <vector>

class AnimatedGameObject
{
public:
	SDL_FRect rect;

	AnimatedGameObject(SDL_Renderer* renderer,
						float x, float y,
						const char* const files[], size_t count,
						Uint64 frameDuration);

	virtual ~AnimatedGameObject();

	virtual void RenderDraw(SDL_Renderer* renderer) const;

	virtual void Update();

protected:
	std::vector<SDL_Texture*> textures;
	size_t currentTextureIndex;
	Uint64 frameDuration;
	Uint64 lastTicks;
};

