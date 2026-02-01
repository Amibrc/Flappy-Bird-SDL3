#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "GameObjectBase.h"

class MultiTextureObject : public GameObjectBase
{
public:
	MultiTextureObject(SDL_Renderer* renderer, float x, float y, const char* const files[], size_t count, bool isPosCenter);
	virtual ~MultiTextureObject() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Switch();

	bool HasTextures() const;
	size_t CurrentTextureIndex() const { return currentTextureIndex; }

protected:
	std::vector<SDL_Texture*> textures;
	size_t currentTextureIndex;
};