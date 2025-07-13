#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "GameObjectBase.h"

class AnimatedGameObject : public GameObjectBase
{
public:
	AnimatedGameObject(SDL_Renderer* renderer,
						float x, float y,
						const char* const files[], size_t count,
						Uint64 frameDuration, bool isPosCenter);
	virtual ~AnimatedGameObject();

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update();

	bool HasTextures() const;

protected:
	std::vector<SDL_Texture*> textures;
	size_t currentTextureIndex;
	Uint64 frameDuration;
	Uint64 lastTicks;
};

