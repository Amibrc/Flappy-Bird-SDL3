#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "GameBase.h"
#include "GameObject.h"
#include "Bird.h"
#include "PipePairsManager.h"
#include "Ground.h"

class Game : GameBase
{
public:
	Game();
	~Game() = default;

	void Iter();
	void EventHandler(SDL_Event* event);
	
private:
	enum class GameState
	{
		StartScreen,
		Playing,
		GameOver
	};

	GameState state;
	Bird bird;
	Ground ground;
	PipePairsManager pipePairsManager;

	GameObject background;
	GameObject gameOverBanner;
	GameObject getReadyBanner;
	GameObject startBanner;

	void RenderDraw();
	void RenderDrawUI();

	void Update();
	void UpdateStartScreen();
	void UpdatePlaying();
	void UpdateGameOver();
	void UpdateCollision();

	void StartPlaying();
	void Restart();
	void Reset();
};