#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "MultiTextureObject.h"

class AnimatedGameObject : public MultiTextureObject
{
public:
	AnimatedGameObject(SDL_Renderer* renderer,
						float x, float y,
						const char* const files[], size_t count,
						bool isPosCenter, Uint64 frameDuration);
	virtual ~AnimatedGameObject() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update(Uint64 nowTicks);

	bool HasTextures() const;

protected:
	Uint64 frameDuration;
	Uint64 lastTicks;
};

