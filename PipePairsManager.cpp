#include <SDL3/SDL.h>

#include "PipePairsManager.hpp"
#include "Collider.hpp"
#include "Config.hpp"

PipePairsManager::PipePairsManager(SDL_Renderer* renderer, float distance) 
	: distance(distance)
{
	for (size_t i = 0; i < SDL_arraysize(pipePairs); i++)
		pipePairs[i] = new PipePair(renderer, WINDOW_WIDTH + i * distance);
}

PipePairsManager::~PipePairsManager()
{
	for (auto& pair : pipePairs)
		delete pair;
}

void PipePairsManager::RenderDraw(SDL_Renderer* renderer) const
{
	for (const auto& pair : pipePairs)
		pair->RenderDraw(renderer);
}

void PipePairsManager::Update()
{
	for (size_t i = 0; i < SDL_arraysize(pipePairs); i++)
	{
		pipePairs[i]->Update();

		if (pipePairs[i]->lowerPipe.rect.x + pipePairs[i]->lowerPipe.rect.w < 0)
		{
			int prevIndex = (i - 1 + SDL_arraysize(pipePairs)) % SDL_arraysize(pipePairs);
			float newX = pipePairs[prevIndex]->lowerPipe.rect.x + distance;

			pipePairs[i]->SetRandomGapPosition();
			pipePairs[i]->SetX(newX);
		}
	}
}

bool PipePairsManager::CheckCollisionWithPipePairs(const SDL_FRect* rect) const 
{
	for (const auto& pair : pipePairs)
	{
		if (Collider::CheckCollision(rect, &pair->lowerPipe.rect) ||
			Collider::CheckCollision(rect, &pair->upperPipe.rect))
			return true;
	}
	return false;
}

void PipePairsManager::Reset()
{
	for (size_t i = 0; i < SDL_arraysize(pipePairs); i++)
	{
		pipePairs[i]->SetX(WINDOW_WIDTH + i * distance);
		pipePairs[i]->SetRandomGapPosition();
	}
}
