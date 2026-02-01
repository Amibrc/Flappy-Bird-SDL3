#pragma once

#include <SDL3/SDL.h>

#include "Collider.h"

class GameObjectBase
{
public:
	GameObjectBase() = default;
	virtual ~GameObjectBase() = default;

	inline const SDL_FRect* Rect() const { return &rect; }

	inline float Width() const { return rect.w; }
	inline float Height() const { return rect.h; }

	inline float Left() const { return rect.x; }
	inline float Right() const { return rect.x + rect.w; }
	inline float Top() const { return rect.y; }
	inline float Bottom() const { return rect.y + rect.h; }

	inline float CenterX() const { return rect.x + rect.w / 2.0f; }
	inline float CenterY() const { return rect.y + rect.h / 2.0f; }

	inline bool IsClicked(float x, float y) const { return Collider::CheckCollision(x, y, &rect); }

	inline void SetX(float newX) { rect.x = newX; }
	inline void SetY(float newY) { rect.y = newY; }

	inline void SetCenterX(float newCenterX) { rect.x = newCenterX - rect.w / 2.0f; }
	inline void SetCenterY(float newCenterY) { rect.y = newCenterY - rect.h / 2.0f; }

	inline void MoveX(float dX) { rect.x += dX; }
	inline void MoveY(float dY) { rect.y += dY; }

	inline void MoveX(float deltaTime, float dX) { rect.x += dX * deltaTime; }
	inline void MoveY(float deltaTime, float dY) { rect.y += dY * deltaTime; }
	
	virtual void RenderDraw(SDL_Renderer* renderer) const = 0;

protected:
	SDL_FRect rect; // Must be initialized in the derived class after texture is loaded
};

