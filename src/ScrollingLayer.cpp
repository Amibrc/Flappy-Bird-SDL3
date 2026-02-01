#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ScrollingLayer.h"
#include "Config.h"

ScrollingLayer::ScrollingLayer(SDL_Renderer* renderer, float y, const char* const file, float speed)
	: speed(speed)
{
	layerPieces.emplace_back(renderer, 0, y, file, false);

	if (!layerPieces.front().HasTexture())
	{
		layerPieces.clear();
		layerPieces.shrink_to_fit();
		return;
	}

	int count = (int)WINDOW_WIDTH / layerPieces.front().Width() + 2;
	layerPieces.reserve(count);

	for (int i = 1; i < count; ++i)
		layerPieces.emplace_back(renderer, layerPieces[i - 1].Right(), y, file, false);
}

void ScrollingLayer::RenderDraw(SDL_Renderer* renderer) const
{
	for (const auto& piece : layerPieces)
		if (piece.Left() < WINDOW_WIDTH)
			piece.RenderDraw(renderer);
}

void ScrollingLayer::Update(float deltaTime)
{
	if (layerPieces.empty())
		return;

	for (auto& piece : layerPieces)
		piece.MoveX(deltaTime, -speed);

	for (auto& piece : layerPieces)
	{
		if (piece.Right() <= 0.0f)
		{
			float maxRight = 0.0f;

			for (const auto& other : layerPieces)
				maxRight = std::max(maxRight, other.Right());

			piece.SetX(maxRight);
		}
	}
}