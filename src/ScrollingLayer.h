#pragma once

#include <SDL3/SDL.h>

#include <vector>
#include <memory>

#include "GameObject.h"

class ScrollingLayer
{
public:
	ScrollingLayer(SDL_Renderer* renderer, float x, float y,
					const char* const file, bool isPosCenter, float speed);
	~ScrollingLayer() = default;

	void RenderDraw(SDL_Renderer* renderer);
	void Update();

private:
	std::vector<std::unique_ptr<GameObject>> layerPieces;
	float speed;
};

