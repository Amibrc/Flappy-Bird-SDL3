#include <SDL3/SDL.h>

#include "PipePair.hpp"
#include "Config.hpp"

PipePair::PipePair(SDL_Renderer* renderer, float x)
	: lowerPipe(renderer, x, 0, false), upperPipe(renderer, x, 0, true)
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
	float newY = (float)SDL_rand((int)(PIPE_MAX_Y - PIPE_MIN_Y + 1)) + PIPE_MIN_Y;
	SetY(newY);
}

void PipePair::SetX(float newX)
{
	lowerPipe.SetX(newX);
	upperPipe.SetX(newX);
}

void PipePair::SetY(float newY)
{
	lowerPipe.SetY(newY + PIPE_PAIR_GAP);
	upperPipe.SetY(newY - lowerPipe.Height());
}