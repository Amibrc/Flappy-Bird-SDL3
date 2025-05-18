#pragma once

#include <SDL3/SDL.h>

#include <vector>

class AnimatedGameObject
{
public:
	AnimatedGameObject(SDL_Renderer* renderer,
						float x, float y,
						const char* const files[], size_t count,
						Uint64 frameDuration,
						bool isPosCenter);
	virtual ~AnimatedGameObject();

	inline const SDL_FRect* Rect() const { return &rect; }

	inline float Width() const { return rect.w; }
	inline float Height() const { return rect.h; }

	inline float Left() const { return rect.x; }
	inline float Right() const { return rect.x + rect.w; };
	inline float Top() const { return rect.y; }
	inline float Down() const { return rect.y + rect.h; };

	inline void SetX(float newX) { rect.x = newX; }
	inline void SetY(float newY) { rect.y = newY; }

	inline void SetCenterX(float newCenterX) { rect.x = newCenterX - rect.w / 2.0f; }
	inline void SetCenterY(float newCenterY) { rect.y = newCenterY - rect.h / 2.0f; }

	inline void MoveX(float dX) { rect.x += dX; }
	inline void MoveY(float dY) { rect.y += dY; }

	virtual void RenderDraw(SDL_Renderer* renderer) const;
	virtual void Update();

protected:
	SDL_FRect rect;
	std::vector<SDL_Texture*> textures;
	size_t currentTextureIndex;
	Uint64 frameDuration;
	Uint64 lastTicks;
};

