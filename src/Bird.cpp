#include <SDL3/SDL.h>

#include "Bird.hpp"
#include "Config.hpp"

Bird::Bird(SDL_Renderer* renderer, float x, float y)
	: AnimatedGameObject(renderer, x, y, birdRedTextureFiles, 3, 100, true),
	velocity(0), alive(true) {}

void Bird::Update()
{
	if (IsAlive())
		AnimatedGameObject::Update();

	if (Down() + velocity < GROUND_Y)
	{
		velocity += GRAVITY;
		rect.y += velocity;
	}
	else
	{
		Death();
		rect.y = (float)GROUND_Y - textures[currentTextureIndex]->h;
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
	rect.x = WINDOW_CENTER_X - (float)textures[currentTextureIndex]->w / 2;
	rect.y = WINDOW_CENTER_Y - (float)textures[currentTextureIndex]->h / 2;
	alive = true;
}

void Bird::Death() { alive = false; }
