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

	void Iter();
	void EventHandler(SDL_Event* event);
	
private:
	enum class GameState
	{
		StartScreen,
		Playing,
		GameOver
	};

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

	void Update();
	void UpdateStartScreen();
	void UpdatePlaying();
	void UpdateGameOver();
	void UpdateCollision();

	void StartPlaying();
	void Restart();
	void Reset();
};