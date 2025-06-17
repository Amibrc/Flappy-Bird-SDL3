#include <SDL3/SDL.h>

#include "Bird.h"
#include "Config.h"

Bird::Bird(SDL_Renderer* renderer)
	: AnimatedGameObject(renderer, WINDOW_CENTER_X, WINDOW_CENTER_Y, birdRedTextureFiles, 3, 100, true),
	idleFlyCounter(0), velocity(0), angle(0), alive(true) {}

void Bird::RenderDraw(SDL_Renderer* renderer) const
{
	SDL_RenderTextureRotated(renderer, textures[currentTextureIndex], nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bird::Update()
{
	if (IsAlive())
	{
		UpdateAngle();

		if (IsFalling())
			currentTextureIndex = BirbFrames::MidFlap;
		else
			AnimatedGameObject::Update();
	}

	UpdateMovement();
}

void Bird::UpdateMovement()
{
	if (Top() + velocity < 0)
	{
		velocity = 0;
		SetY(0);
	}
	else if (Down() + velocity < GROUND_Y)
	{
		velocity += GRAVITY;
		MoveY(velocity);
	}
	else
	{
		Death();
		SetY(GROUND_Y - Height());
	}
}

void Bird::UpdateAngle()
{
	if (velocity < 0)
		angle = BIRD_MIN_ANGLE;
	else if (angle + BIRD_ROTATING_SPEED < BIRD_MAX_ANGLE)
		angle += BIRD_ROTATING_SPEED;
	else
		angle = BIRD_MAX_ANGLE;
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

void Bird::IdleFly()
{
	AnimatedGameObject::Update();
	idleFlyCounter += 0.1f;
	SetCenterY(WINDOW_CENTER_Y + sinf(idleFlyCounter) * 8.0f);
}

