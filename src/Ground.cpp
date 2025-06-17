#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Ground.hpp"
#include "Config.hpp"

Ground::Ground(SDL_Renderer* renderer)
{
	auto first = std::make_unique<GameObject>(renderer, 0, GROUND_Y, grassTextureFile, false);

	if (!first->HasTexture()) return;

	int count = (int)WINDOW_WIDTH / first->Width() + 2;

	groundPieces.reserve(count);
	groundPieces.push_back(std::move(first));

	for (int i = 1; i < count; i++)
		groundPieces.push_back(std::make_unique<GameObject>(renderer, groundPieces[i - 1]->Right(), GROUND_Y, grassTextureFile, false));
}

void Ground::RenderDraw(SDL_Renderer* renderer)
{
	for (const auto& piece : groundPieces)
		piece->RenderDraw(renderer);
}

void Ground::Update()
{
	if (groundPieces.empty()) return;

	float total_len = groundPieces.size() * groundPieces.front()->Width();
	for (auto& piece : groundPieces)
	{
		piece->MoveX(-GROUND_MOVE_SPEED);
		if (piece->Right() < 0)
			piece->MoveX(total_len);
	}
}
