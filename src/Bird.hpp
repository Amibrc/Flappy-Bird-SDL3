#pragma once

#include <SDL3/SDL.h>

#include "AnimatedGameObject.hpp"

class Bird : public AnimatedGameObject
{
public:
	Bird(SDL_Renderer* renderer);

	inline bool IsAlive() const { return alive; }
	inline void Death() { alive = false; }

	void Update() override;
	void Flap();
	void Reset();
	void IdleFly();

private:
	float idleFlyCounter;
	float velocity;
	bool alive;
	
};
