#pragma once

#include <SDL3/SDL.h>

#include <array>

class NumberDisplay
{
public:
	NumberDisplay(const char* fileSuffix);
	virtual ~NumberDisplay();

	virtual SDL_Surface* CreateNumberSurface(size_t number);

protected:
	std::array<SDL_Surface*, 10> digitSurfaces;
	int digitW;
	int digitH;
};

