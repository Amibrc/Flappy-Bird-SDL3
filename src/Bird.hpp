#pragma once

#include <SDL3/SDL.h>

#include "AnimatedGameObject.hpp"

class Bird : public AnimatedGameObject
{
public:
	Bird(SDL_Renderer* renderer, float x, float y);

	void Update() override;

	void Flap();

	void Reset();

	void Death();

	inline bool IsAlive() const { return alive; }

private:
	float velocity;
	bool alive;
};
