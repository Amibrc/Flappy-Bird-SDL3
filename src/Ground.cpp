#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Ground.hpp"
#include "Config.hpp"

Ground::Ground(SDL_Renderer* renderer)
{
	groundPieces[0] = new GameObject(renderer, 0, GROUND_Y, grassTextureFile, false);
	groundPieces[1] = new GameObject(renderer, groundPieces[0]->Right(), GROUND_Y, grassTextureFile, false);
}

Ground::~Ground()
{
	delete groundPieces[0];
	delete groundPieces[1];
}

void Ground::RenderDraw(SDL_Renderer* renderer)
{
	for (const auto& piece : groundPieces)
		piece->RenderDraw(renderer);
}

void Ground::Update()
{
	for (auto& piece : groundPieces)
	{
		piece->rect.x -= GROUND_MOVE_SPEED;

		if (piece->Right() < 0)
		{
			GameObject* other = (piece == groundPieces[0]) ? groundPieces[1] : groundPieces[0];
			piece->rect.x = other->Right() - GROUND_MOVE_SPEED;
		}
	}
}
