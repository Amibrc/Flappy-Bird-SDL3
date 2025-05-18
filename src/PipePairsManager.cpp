#include <SDL3/SDL.h>

#include "PipePairsManager.hpp"
#include "Collider.hpp"
#include "Config.hpp"

PipePairsManager::PipePairsManager(SDL_Renderer* renderer) 
{
	pipePairs[0] = std::make_unique<PipePair>(renderer, PIPE_PAIRS_START_X);
	for (int i = 1; i < PIPE_PAIRS_COUNT; i++)
		pipePairs[i] = std::make_unique<PipePair>(renderer, pipePairs[i - 1]->Right() + PIPE_PAIRS_DISTANCE);
}

void PipePairsManager::RenderDraw(SDL_Renderer* renderer) const
{
	for (const auto& pair : pipePairs)
		pair->RenderDraw(renderer);
}

void PipePairsManager::Update()
{
	for (int i = 0; i < PIPE_PAIRS_COUNT; i++)
	{
		pipePairs[i]->Update();

		if (pipePairs[i]->Right() < 0)
		{
			int prevIndex = (i - 1 + PIPE_PAIRS_COUNT) % PIPE_PAIRS_COUNT;
			float newX = pipePairs[prevIndex]->Right() + PIPE_PAIRS_DISTANCE;

			pipePairs[i]->SetRandomGapPosition();
			pipePairs[i]->SetX(newX);
		}
	}
}

bool PipePairsManager::CheckCollisionWithPipePairs(const SDL_FRect* rect) const 
{
	for (const auto& pair : pipePairs)
	{
		if (Collider::CheckCollision(rect, pair->LowerPipeRect()) ||
			Collider::CheckCollision(rect, pair->UpperPipeRect()))
			return true;
	}
	return false;
}

void PipePairsManager::Reset()
{
	pipePairs[0]->SetX(PIPE_PAIRS_START_X);
	pipePairs[0]->SetRandomGapPosition();
	for (int i = 1; i < PIPE_PAIRS_COUNT; i++)
	{
		pipePairs[i]->SetX(pipePairs[i - 1]->Right() + PIPE_PAIRS_DISTANCE);
		pipePairs[i]->SetRandomGapPosition();
	}
}
