#include <SDL3/SDL.h>

#include "PipePair.hpp"
#include "Config.hpp"

PipePair::PipePair(SDL_Renderer* renderer, float x)
	: lowerPipe(renderer, x, 0, false), upperPipe(renderer, x, 0, true), gap(200)
{
	SetRandomGapPosition();
}

void PipePair::RenderDraw(SDL_Renderer* renderer) const
{
	lowerPipe.RenderDraw(renderer);
	upperPipe.RenderDraw(renderer);
}

void PipePair::Update()
{
	lowerPipe.Update();
	upperPipe.Update();
}

void PipePair::SetRandomGapPosition()
{
	const float minY = 100.f;
	const float maxY = GROUND_Y - gap - 100.f;

	float newY = (float)SDL_rand((int)(maxY - minY + 1)) + minY;

	SetY(newY);
}

void PipePair::SetX(float newX) 
{
	lowerPipe.rect.x = newX;
	upperPipe.rect.x = newX;
}

void PipePair::SetY(float newY)
{
	lowerPipe.rect.y = newY + gap;
	upperPipe.rect.y = newY - lowerPipe.rect.h;
}