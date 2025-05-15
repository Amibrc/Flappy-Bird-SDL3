#pragma once

#include <SDL3/SDL.h>

#include "Pipe.hpp"

class PipePair
{
public:
    Pipe lowerPipe;
    Pipe upperPipe;

    PipePair(SDL_Renderer* renderer, float x);

    void RenderDraw(SDL_Renderer* renderer) const;

    void Update();

    void SetX(float newX);

    void SetY(float newY);

    void SetRandomGapPosition();
};