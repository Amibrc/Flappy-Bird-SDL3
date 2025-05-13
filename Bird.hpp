#pragma once

#include <SDL3/SDL.h>

#include "AnimatedGameObject.hpp"

class Bird : public AnimatedGameObject
{
public:
	int velocity;
	int gravity;

	Bird(SDL_Renderer* renderer, float x, float y);

	void Update() override;

	void Flap();

	void Reset();

	void Death();

	inline bool IsAlive() { return alive; }

private:
	bool alive;
};
