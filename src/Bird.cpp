#include <SDL3/SDL.h>

#include "Bird.hpp"
#include "Config.hpp"

Bird::Bird(SDL_Renderer* renderer, float x, float y)
	: AnimatedGameObject(renderer, x, y, birdYellowTextureFiles, 3, 150), velocity(0), gravity(2), alive(true)
{
	rect.x -= textures[currentTextureIndex]->w / 2;
	rect.y -= textures[currentTextureIndex]->h / 2;
}


void Bird::Update()
{
	if (IsAlive())
		AnimatedGameObject::Update();

	if (rect.y + textures[currentTextureIndex]->h + velocity < GROUND_Y)
	{
		velocity += gravity;
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
		velocity = -20;
}

void Bird::Reset()
{
	velocity = 0;
	currentTextureIndex = 0;
	lastTicks = 0;
	rect.x = WINDOW_WIDTH / 2 - textures[currentTextureIndex]->w / 2;
	rect.y = WINDOW_HEIGHT / 2 - textures[currentTextureIndex]->h / 2;
	alive = true;
}

void Bird::Death() { alive = false; }
