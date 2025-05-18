#include <SDL3/SDL.h>

#include "Bird.hpp"
#include "Config.hpp"

Bird::Bird(SDL_Renderer* renderer)
	: AnimatedGameObject(renderer, WINDOW_CENTER_X, WINDOW_CENTER_Y, birdRedTextureFiles, 3, 100, true),
	idleFlyCounter(0), velocity(0), alive(true) {}

void Bird::Update()
{
	if (IsAlive())
		AnimatedGameObject::Update();

	if (Down() + velocity < GROUND_Y)
	{
		velocity += GRAVITY;
		MoveY(velocity);
	}
	else
	{
		Death();
		SetY((float)GROUND_Y - Height());
	}
}

void Bird::Flap()
{
	if (IsAlive())
		velocity = -BIRD_FLAP_FORCE;
}

void Bird::Reset()
{
	velocity = 0;
	currentTextureIndex = 0;
	lastTicks = 0;
	alive = true;
	SetCenterY(WINDOW_CENTER_Y);
}

void Bird::IdleFly()
{
	AnimatedGameObject::Update();
	idleFlyCounter += 0.1f;
	SetY(WINDOW_CENTER_Y + (float)sin(idleFlyCounter) * 8.0f);
}

