#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, float x, float y, const char* file, bool isPosCenter);
	virtual ~GameObject();

	inline const SDL_FRect* Rect() const { return &rect; }

	inline float Width() const { return rect.w; }
	inline float Height() const { return rect.h; }

	inline float Left() const { return rect.x; }
	inline float Right() const { return rect.x + rect.w; }
	inline float Top() const { return rect.y; }
	inline float Down() const { return rect.y + rect.h; }

	inline void SetX(float newX) { rect.x = newX; }
	inline void SetY(float newY) { rect.y = newY; }

	inline void SetCenterX(float newCenterX) { rect.x = newCenterX - rect.w / 2.0f; }
	inline void SetCenterY(float newCenterY) { rect.y = newCenterY - rect.h / 2.0f; }

	inline void MoveX(float dX) { rect.x += dX; }
	inline void MoveY(float dY) { rect.y += dY; }

	virtual void RenderDraw(SDL_Renderer* renderer) const;
	
protected:
	SDL_FRect rect;
	SDL_Texture* texture;
};
