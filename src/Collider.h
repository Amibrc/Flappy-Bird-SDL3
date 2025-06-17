#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Collider
{
public:
    static inline bool CheckCollisionX(const SDL_FRect* rect1, const SDL_FRect* rect2)
    {
        return (rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x);
    }

    static inline bool CheckCollisionY(const SDL_FRect* rect1, const SDL_FRect* rect2)
    {
        return (rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y);
    }

    static inline bool CheckCollision(const SDL_FRect* rect1, const SDL_FRect* rect2)
    {
        return CheckCollisionX(rect1, rect2) && CheckCollisionY(rect1, rect2);
    }
};