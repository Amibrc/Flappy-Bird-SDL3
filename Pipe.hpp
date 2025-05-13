#pragma once

#include <SDL3/SDL.h>

#include "GameObject.hpp"

class Pipe : public GameObject
{
public:
	Pipe(SDL_Renderer* renderer, float x, float y, bool flipped);

	void RenderDraw(SDL_Renderer* renderer) const override;

	void Update();

private:
	bool flipped;
};