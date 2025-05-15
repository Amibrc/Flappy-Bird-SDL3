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
						Uint64 frameDuration,
						bool isPosCenter);

	virtual ~AnimatedGameObject();

	virtual void RenderDraw(SDL_Renderer* renderer) const;

	virtual void Update();

	inline float Left() const { return rect.x; }
	inline float Right() const { return rect.x + rect.w; };
	inline float Top() const { return rect.y; }
	inline float Down() const { return rect.y + rect.h; };

protected:
	std::vector<SDL_Texture*> textures;
	size_t currentTextureIndex;
	Uint64 frameDuration;
	Uint64 lastTicks;
};

