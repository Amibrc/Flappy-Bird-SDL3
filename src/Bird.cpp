#include <SDL3/SDL.h>

#include "Bird.h"
#include "Config.h"

Bird::Bird(SDL_Renderer* renderer)
	: AnimatedGameObject(renderer, WINDOW_CENTER_X, WINDOW_CENTER_Y, birdRedFiles, 3, true, 100),
	idleFlyCounter(0), velocity(0), angle(0), alive(true) {}

void Bird::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTextureRotated(renderer, textures[currentTextureIndex], nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bird::Update(float deltaTime, Uint64 nowTicks)
{
	UpdateMovement(deltaTime);
	UpdateCollision();
	UpdateAngleAndAnimation(deltaTime, nowTicks);
}

void Bird::UpdateCollision()
{
	if (Top() < TOP_GROUND_Y)
	{
		SetY(TOP_GROUND_Y);
		velocity = 0;
	}
	else if (Bottom() > BOTTOM_GROUND_Y)
	{
		SetY(BOTTOM_GROUND_Y - Height());
		Death();
	}
}

void Bird::UpdateMovement(float deltaTime)
{
	velocity += GRAVITY * deltaTime;
	MoveY(deltaTime, velocity);
}

void Bird::UpdateAngleAndAnimation(float deltaTime, Uint64 nowTicks)
{
	if (velocity < 0)
	{
		angle = BIRD_MIN_ANGLE;

		if (IsAlive())
			AnimatedGameObject::Update(nowTicks);
	}
	else
	{
		if (IsAlive())
		{
			angle += BIRD_ROTATING_SPEED * deltaTime;
			AnimatedGameObject::Update(nowTicks);
		}
		else
			angle += BIRD_ROTATING_SPEED * 2 * deltaTime;

		if (angle > BIRD_MAX_ANGLE)
		{
			angle = BIRD_MAX_ANGLE;
			currentTextureIndex = (size_t)BirbFrames::MidFlap;
		}
	}
}

void Bird::Flap()
{
	if (IsAlive())
		velocity = -BIRD_FLAP_FORCE;
}

void Bird::Death()
{
	alive = false;
	currentTextureIndex = (size_t)BirbFrames::MidFlap;
}

void Bird::Reset()
{
	velocity = 0;
	currentTextureIndex = 0;
	lastTicks = 0;
	angle = 0;
	alive = true;
	SetCenterY(WINDOW_CENTER_Y);
}

void Bird::IdleFly(float deltaTime, Uint64 nowTicks)
{
	AnimatedGameObject::Update(nowTicks);
	idleFlyCounter += BIRD_COUNTER * deltaTime;
	SetCenterY(WINDOW_CENTER_Y + sinf(idleFlyCounter) * 8.0f);
}

