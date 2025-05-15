#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameObject
{
public:
	SDL_FRect rect;

	GameObject(SDL_Renderer* renderer, float x, float y, const char* file, bool isPosCenter);

	virtual ~GameObject();

	virtual void RenderDraw(SDL_Renderer* renderer) const;

	inline float Left() const { return rect.x; }
	inline float Right() const { return rect.x + rect.w; };
	inline float Top() const { return rect.y; }
	inline float Down() const { return rect.y + rect.h; };
	
protected:
	SDL_Texture* texture;
};
