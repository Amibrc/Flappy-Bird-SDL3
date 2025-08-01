#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>

#include "NumberDisplay.h"

NumberDisplay::NumberDisplay(const char* fileSuffix)
{
	for (int i = 0; i < 10; ++i)
	{
		std::string file = "assets/" + std::to_string(i) + fileSuffix;
		digitSurfaces[i] = IMG_Load(file.c_str());

		if (!digitSurfaces[i])
			SDL_Log("Error to load surface [%s]", SDL_GetError());
	}

	for (const auto& surf : digitSurfaces)
	{
		if (surf)
		{
			digitW = surf->w;
			digitH = surf->h;
			return;
		}
	}

	digitW = 0;
	digitH = 0;
}

NumberDisplay::~NumberDisplay()
{
	for (auto& surface : digitSurfaces)
		SDL_DestroySurface(surface);
}

SDL_Surface* NumberDisplay::CreateNumberSurface(size_t number)
{
	std::string strNumber = std::to_string(number);

	size_t totalWidth = 0;
	for (char c : strNumber)
	{
		int digit = c - '0';
		if (digitSurfaces[digit])
			totalWidth += digitSurfaces[digit]->w;
	}
	
	SDL_Rect dstrect = { 0, 0, totalWidth, digitH };
	SDL_Surface* surface = SDL_CreateSurface(totalWidth, digitH, SDL_PIXELFORMAT_ABGR32);

	if (!surface)
	{
		SDL_Log("Error to create surface [%s]", SDL_GetError());
		return nullptr;
	}

	for (char c : strNumber)
	{
		int digit = c - '0';
		if (digitSurfaces[digit])
		{
			SDL_BlitSurface(digitSurfaces[digit], nullptr, surface, &dstrect);
			dstrect.x += digitSurfaces[digit]->w;
		}
	}

	return surface;
}