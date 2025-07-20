#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SDL_Base.h"
#include "GameObject.h"
#include "ScrollingLayer.h"
#include "Bird.h"
#include "PipePairsManager.h"
#include "Score.h"
#include "Stats.h"

class Game : SDL_Base
{
public:
	Game();
	~Game() = default;

	SDL_AppResult Iter();
	SDL_AppResult EventHandler(SDL_Event* event);
	
private:
	enum class GameState
	{
		StartScreen,
		Playing,
		GameOver
	};

	Uint64 lastTicks;

	GameObject gameOverBanner;
	GameObject getReadyBanner;
	GameObject startBanner;

	ScrollingLayer background;
	ScrollingLayer ground;

	Bird bird;
	GameState state;
	PipePairsManager pipePairsManager;
	Score score;
	Stats stats;

	void RenderDraw();
	void RenderDrawUI();

	void Update(float deltaTime, Uint64 nowTicks);
	void UpdateStartScreen(float deltaTime, Uint64 nowTicks);
	void UpdatePlaying(float deltaTime, Uint64 nowTicks);
	void UpdateGameOver(float deltaTime, Uint64 nowTicks);
	void UpdateCollision();

	void StartPlaying();
	void Restart();
	void Reset();
};