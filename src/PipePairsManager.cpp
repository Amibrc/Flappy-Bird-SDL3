#include <SDL3/SDL.h>

#include "PipePairsManager.h"
#include "Collider.h"
#include "Config.h"

PipePairsManager::PipePairsManager(SDL_Renderer* renderer)
{
	pipePairs.reserve(PIPE_PAIRS_COUNT);
	pipePairs.emplace_back(renderer, PIPE_PAIRS_START_X);

	if (!pipePairs.front().Lower()->HasTexture())
	{
		pipePairs.clear();
		pipePairs.shrink_to_fit();
		return;
	}

	for (int i = 1; i < PIPE_PAIRS_COUNT; ++i)
		pipePairs.emplace_back(renderer, pipePairs[i - 1].Right() + PIPE_PAIRS_DISTANCE);
}

void PipePairsManager::RenderDraw(SDL_Renderer* renderer) const
{
	for (const auto& pair : pipePairs)
		if (pair.Left() < WINDOW_WIDTH)
			pair.RenderDraw(renderer);
}

void PipePairsManager::Update(float deltaTime)
{
	for (int i = 0; i < PIPE_PAIRS_COUNT; ++i)
	{
		pipePairs[i].Update(deltaTime);

		if (pipePairs[i].Right() <= 0)
		{
			int prevIndex = (i - 1 + PIPE_PAIRS_COUNT) % PIPE_PAIRS_COUNT;
			float newX = pipePairs[prevIndex].Right() + PIPE_PAIRS_DISTANCE;

			pipePairs[i].SetRandomGapPosition();
			pipePairs[i].SetX(newX);
			pipePairs[i].Reset();
		}
	}
}

bool PipePairsManager::CheckCollisionWithPipePairs(const SDL_FRect* rect) const 
{
	for (const auto& pair : pipePairs)
	{
		if (Collider::CheckCollision(rect, pair.Lower()->Rect()) ||
			Collider::CheckCollision(rect, pair.Upper()->Rect()))
			return true;
	}
	return false;
}

bool PipePairsManager::IsPassedBy(float targetX)
{
	for (auto& pair : pipePairs)
	{
		if (targetX > pair.Left() && !pair.IsPassedBy())
		{
			pair.Passed();
			return true;
		}
	}
	return false;
}

void PipePairsManager::Reset()
{
	pipePairs[0].SetX(PIPE_PAIRS_START_X);
	pipePairs[0].SetRandomGapPosition();
	pipePairs[0].Reset();
	for (int i = 1; i < PIPE_PAIRS_COUNT; ++i)
	{
		pipePairs[i].SetX(pipePairs[i - 1].Right() + PIPE_PAIRS_DISTANCE);
		pipePairs[i].SetRandomGapPosition();
		pipePairs[i].Reset();
	}
}
