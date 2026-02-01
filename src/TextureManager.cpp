#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "TextureManager.h"

std::unordered_map<std::string, SDL_Texture*> TextureManager::textureCache;
std::unordered_map<std::string, SDL_Surface*> TextureManager::surfaceCache;

SDL_Texture* TextureManager::GetTexture(SDL_Renderer* renderer, const char* const file)
{
	std::string key = file;

	auto it = textureCache.find(key);
	if (it != textureCache.end())
		return it->second;

	SDL_Texture* texture = IMG_LoadTexture(renderer, file);
	if (!texture)
	{
		SDL_Log("TextureManager( Error to load texture: [%s] )", SDL_GetError());
		return nullptr;
	}

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	textureCache[key] = texture;
	return texture;
}

SDL_Surface* TextureManager::GetSurface(const char* const file)
{
	std::string key = file;

	auto it = surfaceCache.find(key);
	if (it != surfaceCache.end())
		return it->second;

	SDL_Surface* surface = IMG_Load(file);
	if (!surface)
	{
		SDL_Log("TextureManager: Error to load surface: [%s]", SDL_GetError());
		return nullptr;
	}

	surfaceCache[key] = surface;
	return surface;
}

void TextureManager::Clear()
{
	for (auto& pair : textureCache)
		SDL_DestroyTexture(pair.second);
	textureCache.clear();

	for (auto& pair : surfaceCache)
		SDL_DestroySurface(pair.second);
	surfaceCache.clear();
}
