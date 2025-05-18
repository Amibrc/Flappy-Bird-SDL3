#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "GameBase.hpp"
#include "GameObject.hpp"
#include "Bird.hpp"
#include "PipePairsManager.hpp"
#include "Ground.hpp"

class Game : GameBase
{
public:
	Game();

	void Iter();
	void EventHandler(SDL_Event* event);
	
private:
	enum class GameState
	{
		startScreen,
		playing,
		gameOver
	};

	GameState state;
	Bird bird;
	Ground ground;
	PipePairsManager pipePairsManager;

	GameObject background;
	GameObject gameOverBanner;
	GameObject getReadyBanner;

	void RenderDraw();
	void RenderDrawUI();

	void Update();
	void UpdateStartScreen();
	void UpdatePlaying();
	void UpdateGameOver();
	void UpdateCollision();

	void StartPlaying();
	void Restart();
};