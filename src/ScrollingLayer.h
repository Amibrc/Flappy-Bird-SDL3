#pragma once

#include <SDL3/SDL.h>

#include <vector>
#include <memory>

#include "GameObject.h"

class ScrollingLayer
{
public:
	ScrollingLayer(SDL_Renderer* renderer, float y, const char* const file, float speed);
	~ScrollingLayer() = default;

	void RenderDraw(SDL_Renderer* renderer) const;
	void Update();

private:
	std::vector<std::unique_ptr<GameObject>> layerPieces;
	float speed;
};

