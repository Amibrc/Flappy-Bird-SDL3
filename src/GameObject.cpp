#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "TextureManager.h"

#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, float x, float y, const char* const file, bool isPosCenter)
	: texture(TextureManager::GetTexture(renderer, file))
{
	if (!texture)
	{
		rect = { x, y, 0, 0 };
		return;
	}
	
	if (isPosCenter)
		rect = { x - texture->w / 2.0f, y - texture->h / 2.0f, (float)texture->w, (float)texture->h };
	else
		rect = { x, y, (float)texture->w, (float)texture->h };
};

void GameObject::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
