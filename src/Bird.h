#pragma once

#include <SDL3/SDL.h>

#include "AnimatedGameObject.h"
#include "Config.h"

class Bird : public AnimatedGameObject
{
public:
	Bird(SDL_Renderer* renderer);
	~Bird() = default;

	inline bool IsAlive() const { return alive; }
	inline bool IsFalling() const { return angle == BIRD_MAX_ANGLE; }
	inline void Death() { alive = false; }

	void RenderDraw(SDL_Renderer* renderer) const override;
	void Update() override;

	void Flap();
	void Reset();
	void IdleFly();

private:
	enum BirbFrames
	{
		UpFlap,
		MidFlap,
		DownFlap
	};

	float idleFlyCounter;
	float velocity;
	float angle;
	bool alive;

	void UpdateMovement();
	void UpdateAngle();
};
