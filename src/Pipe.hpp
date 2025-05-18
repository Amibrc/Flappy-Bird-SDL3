#pragma once

#include <SDL3/SDL.h>

#include "GameObject.hpp"
#include "Config.hpp"

class Pipe : public GameObject
{
public:
	Pipe(SDL_Renderer* renderer, float x, float y, bool flipped);

	void RenderDraw(SDL_Renderer* renderer) const override;
	inline void Update() { rect.x -= PIPE_MOVE_SPEED; }

private:
	bool flipped;
};