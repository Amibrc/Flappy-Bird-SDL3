#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ScrollingLayer.h"
#include "Config.h"

ScrollingLayer::ScrollingLayer(SDL_Renderer* renderer, float y, const char* const file, float speed)
	: speed(speed)
{
	auto first = std::make_unique<GameObject>(renderer, 0, y, file, false);

	if (!first->HasTexture())
		return;

	int count = (int)WINDOW_WIDTH / first->Width() + 2;

	layerPieces.reserve(count);
	layerPieces.push_back(std::move(first));

	for (int i = 1; i < count; ++i)
		layerPieces.push_back(std::make_unique<GameObject>(renderer, layerPieces[i - 1]->Right(), y, file, false));
}

void ScrollingLayer::RenderDraw(SDL_Renderer* renderer) const
{
	for (const auto& piece : layerPieces)
		if (piece->Left() < WINDOW_WIDTH)
			piece->RenderDraw(renderer);
}

void ScrollingLayer::Update(float deltaTime)
{
	if (layerPieces.empty())
		return;

	for (auto& piece : layerPieces)
	{
		piece->MoveX(deltaTime, -speed);
		if (piece->Right() <= 0)
			piece->MoveX(layerPieces.size() * layerPieces.front()->Width());
	}
}