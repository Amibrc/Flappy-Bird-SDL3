#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameObject
{
public:
	SDL_FRect rect;

	GameObject(SDL_Renderer* renderer, float x, float y, const char* file);

	virtual ~GameObject();

	virtual void RenderDraw(SDL_Renderer* renderer) const;

protected:
	SDL_Texture* texture;
};
