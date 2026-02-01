#pragma once

#include <SDL3/SDL.h>

#include "AnimatedGameObject.h"
#include "Config.h"

class Bird : public AnimatedGameObject
{
public:
	Bird(SDL_Renderer* renderer, float x, float y, bool isPosCenter);
	~Bird() = default;

	inline bool IsAlive() const { return alive; }
	inline void SetIdleBaseY(float newY) { idleBaseY = newY; }

	void RenderDraw(SDL_Renderer* renderer) const override;
	void Update(float deltaTime, Uint64 nowTicks);
	void IdleFly(float deltaTime, Uint64 nowTicks);

	void Flap();
	void Death();
	void Reset();

private:
	enum class BirbFrames
	{
		UpFlap,
		MidFlap,
		DownFlap
	};

	float idleFlyCounter;
	float idleBaseY;
	float velocity;
	float angle;
	bool alive;

	void UpdateCollision();
	void UpdateMovement(float deltaTime);
	void UpdateAngleAndAnimation(float deltaTime, Uint64 nowTicks);
};
