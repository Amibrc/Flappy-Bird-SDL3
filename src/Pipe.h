#pragma once

#include <SDL3/SDL.h>

#include "GameObject.h"
#include "Config.h"

class Pipe : public GameObject
{
public:
	Pipe(SDL_Renderer* renderer, float x, float y, bool flipped);
	~Pipe() = default;

	void RenderDraw(SDL_Renderer* renderer) const override;
	inline void Update(float deltaTime) { rect.x -= PIPE_MOVE_SPEED * deltaTime; }

private:
	bool flipped;
};