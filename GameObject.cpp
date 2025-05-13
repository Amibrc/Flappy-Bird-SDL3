#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "GameObject.hpp"

GameObject::GameObject(SDL_Renderer* renderer, float x, float y, const char* file)
	: texture(IMG_LoadTexture(renderer, file))
{
	if (!texture)
	{
		SDL_Log("Error: IMG_LoadTexture - %s", SDL_GetError());
		rect = { x, y, 0, 0 };
		return;
	}
	
	rect = { x, y, (float)texture->w, (float)texture->h };
};

GameObject::~GameObject() { SDL_DestroyTexture(texture); }

void GameObject::RenderDraw(SDL_Renderer* renderer) const
	{ SDL_RenderTexture(renderer, texture, nullptr, &rect); }

