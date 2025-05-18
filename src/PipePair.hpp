#pragma once

#include <SDL3/SDL.h>

#include "Pipe.hpp"

class PipePair
{
public:
    PipePair(SDL_Renderer* renderer, float x);

    inline const SDL_FRect* LowerPipeRect() const { return lowerPipe.Rect(); }
    inline const SDL_FRect* UpperPipeRect() const { return upperPipe.Rect(); }

    inline float Left() const { return lowerPipe.Left(); }
    inline float Right() const { return lowerPipe.Right(); }

    void SetX(float newX);
    void SetY(float newY);
    void SetRandomGapPosition();

    void RenderDraw(SDL_Renderer* renderer) const;
    void Update();

private:
    Pipe lowerPipe;
    Pipe upperPipe;
};