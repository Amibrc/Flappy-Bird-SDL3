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
	void Update(float deltaTime, Uint64 nowTicks);

	void Flap();
	void Reset();
	void IdleFly(float deltaTime, Uint64 nowTicks);

private:
	enum class BirbFrames
	{
		UpFlap,
		MidFlap,
		DownFlap
	};

	float idleFlyCounter;
	float velocity;
	float angle;
	bool alive;

	void UpdateMovement(float deltaTime);
	void UpdateAngle(float deltaTime);
};
