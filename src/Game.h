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
#include "MultiTextureObject.h"

class Game : SDL_Base
{
public:
	Game();
	~Game();

	[[nodiscard]] SDL_AppResult Iter();
	[[nodiscard]] SDL_AppResult EventHandler(SDL_Event* event);
	
private:
	// ==== Types ====
	enum class GameState
	{
		MainScreen,
		StartScreen,
		Playing,
		GameOver
	};

	// ==== States ====
	bool pause;
	GameState state;
	Uint64 lastTicks;

	// ==== Game objects ====
	Bird bird;
	PipePairsManager pipePairsManager;
	ScrollingLayer background;
	ScrollingLayer ground;

	// ==== UI ====
	GameObject gameOverBanner;
	GameObject getReadyBanner;
	GameObject startBanner;
	GameObject flappyBirdBanner;
	GameObject startButton;
	GameObject menuButton;
	GameObject okButton;
	MultiTextureObject pauseButton;

	// ==== Score / Stats ====
	Score score;
	Stats stats;

	// ==== Input handlers ====
	void HandleMouseClick(float x, float y);
	void HandleKeyPress(const SDL_KeyboardEvent* keyEvent);
	void HandleGameAction();

	// ==== Rendering ====
	void RenderDraw();
	void RenderDrawUI();

	// ==== Updates ====
	void Update(float deltaTime, Uint64 nowTicks);
	void UpdateMainScreen(float deltaTime, Uint64 nowTicks);
	void UpdateStartScreen(float deltaTime, Uint64 nowTicks);
	void UpdatePlaying(float deltaTime, Uint64 nowTicks);
	void UpdateGameOver(float deltaTime, Uint64 nowTicks);
	void UpdateCollision();

	// ==== State transitions ====
	void StartPlaying();
	void Restart();
	void Reset();

	void TogglePause();
	void PauseOff();
};