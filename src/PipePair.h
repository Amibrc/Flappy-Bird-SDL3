#pragma once

#include <SDL3/SDL.h>

#include "Pipe.h"

class PipePair
{
public:
    PipePair(SDL_Renderer* renderer, float x);
    ~PipePair() = default;

    inline const Pipe* Lower() const { return &lowerPipe; }
    inline const Pipe* Upper() const { return &upperPipe; }

    inline float Left() const { return lowerPipe.Left(); }
    inline float Right() const { return lowerPipe.Right(); }

    inline void Reset() { isPassedBy = false; }
    inline void Passed() { isPassedBy = true; }
    inline bool IsPassedBy() const { return isPassedBy; }

    void SetX(float newX);
    void SetY(float newY);
    void SetRandomGapPosition();

    void RenderDraw(SDL_Renderer* renderer) const;
    void Update(float deltaTime);
    
private:
    bool isPassedBy;

    Pipe lowerPipe;
    Pipe upperPipe;
};