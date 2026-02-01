#pragma once

#include <SDL3/SDL.h>

#include "GameObjectBase.h"

class GameObject : public GameObjectBase
{
public:
	GameObject(SDL_Renderer* renderer, float x, float y, const char* const file, bool isPosCenter);
	virtual ~GameObject() = default;

	inline bool HasTexture() const { return texture != nullptr; }
	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	
protected:
	SDL_Texture* texture;
};
