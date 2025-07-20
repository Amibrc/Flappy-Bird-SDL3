#include <SDL3/SDL.h>

#include "Bird.h"
#include "Config.h"

Bird::Bird(SDL_Renderer* renderer)
	: AnimatedGameObject(renderer, WINDOW_CENTER_X, WINDOW_CENTER_Y, birdRedFiles, 3, 100, true),
	idleFlyCounter(0), velocity(0), angle(0), alive(true) {}

void Bird::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTextureRotated(renderer, textures[currentTextureIndex], nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bird::Update(float deltaTime, Uint64 nowTicks)
{
	if (IsAlive())
	{
		UpdateAngle(deltaTime);

		if (IsFalling())
			currentTextureIndex = (size_t)BirbFrames::MidFlap;
		else
			AnimatedGameObject::Update(nowTicks);
	}

	UpdateMovement(deltaTime);
}

void Bird::UpdateMovement(float deltaTime)
{
	velocity += GRAVITY * deltaTime;
	MoveY(deltaTime, velocity);

	if (Top() <= 0)
	{
		SetY(0);
		velocity = 0;
	}
	else if (Bottom() >= GROUND_Y)
	{
		SetY(GROUND_Y - Height());
		Death();
	}
}

void Bird::UpdateAngle(float deltaTime)
{
	if (velocity < 0)
		angle = BIRD_MIN_ANGLE;
	else
	{
		angle += BIRD_ROTATING_SPEED * deltaTime;
		if (angle > BIRD_MAX_ANGLE)
			angle = BIRD_MAX_ANGLE;
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

