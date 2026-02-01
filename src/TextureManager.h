#pragma once

#include <SDL3/SDL.h>

#include <unordered_map>

#include <string>

class TextureManager
{
public:
	static SDL_Texture* GetTexture(SDL_Renderer* renderer, const char* const file);
	static SDL_Surface* GetSurface(const char* const file);
	static void Clear();

private:
	static std::unordered_map<std::string, SDL_Texture*> textureCache;
	static std::unordered_map<std::string, SDL_Surface*> surfaceCache;
};
