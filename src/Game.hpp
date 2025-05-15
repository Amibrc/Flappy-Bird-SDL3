#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "GameObject.hpp"
#include "Bird.hpp"
#include "PipePairsManager.hpp"
#include "Ground.hpp"

class Game
{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Bird* bird;
	GameObject* background;
	Ground* ground;
	GameObject* gameOverBanner;
	PipePairsManager* pipePairsManager;

	Game();

	~Game();

	void Iter();

	void EventHandler(SDL_Event* event);

	void Restart();

private:
	void RenderDraw();

	void Update();

	void UpdateCollision();
};