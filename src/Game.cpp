#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.h"
#include "Config.h"
#include "Collider.h"

Game::Game()
	: state(GameState::StartScreen),
	lastTicks(SDL_GetTicks()), bird(renderer), pipePairsManager(renderer),
	background(renderer, 0, backgroundNightFile, BACKGROUND_MOVE_SPEED),
	ground(renderer, BOTTOM_GROUND_Y, groundFile, GROUND_MOVE_SPEED),
	gameOverBanner(renderer, WINDOW_CENTER_X, 200, gameOverBannerFile, true),
	getReadyBanner(renderer, WINDOW_CENTER_X, 200, getReadyBannerFile, true),
	startBanner(renderer, WINDOW_CENTER_X, 520, startBannerFile, true),
	pauseButton(renderer, 20, 20, pauseButtonFiles, 2, false),
	okButton(renderer, WINDOW_CENTER_X, 600, okButtonFile, true),
	score(renderer), stats(renderer), pause(false) {}

SDL_AppResult Game::Iter()
{
	Uint64 nowTicks = SDL_GetTicks();
	float deltaTime = (nowTicks - lastTicks) / 1000.0f;
	lastTicks = nowTicks;

	Update(deltaTime, nowTicks);
	RenderDraw();

	Uint64 frameTime = SDL_GetTicks() - nowTicks;
	if (frameTime < DELAY_MS)
		SDL_Delay(DELAY_MS - frameTime);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::EventHandler(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		HandleMouseClick(event->button.x, event->button.y);
		break;

	case SDL_EVENT_KEY_DOWN:
		HandleKeyPress(&event->key);
		break;
	}

	return SDL_APP_CONTINUE;
}

void Game::HandleMouseClick(float x, float y)
{
	if (pauseButton.IsClicked(x, y))
	{
		TogglePause();
		return;
	}

	if (!pause)
	{
		HandleGameAction();
		if (state == GameState::GameOver && okButton.IsClicked(x, y))
			Restart();
	}
}

void Game::HandleKeyPress(const SDL_KeyboardEvent* keyEvent)
{
	if (keyEvent->repeat)
		return;

	switch (keyEvent->scancode)
	{
	case SDL_SCANCODE_SPACE:
		HandleGameAction();
		break;

	case SDL_SCANCODE_ESCAPE:
		TogglePause();
		break;
	}
}

void Game::HandleGameAction()
{
	switch (state)
	{
	case GameState::Playing:
		bird.Flap();
		break;

	case GameState::StartScreen:
		StartPlaying();
		break;
	}
}

void Game::RenderDraw()
{
	background.RenderDraw(renderer);
	
	if (state != GameState::StartScreen)
	{
		pipePairsManager.RenderDraw(renderer);
		score.RenderDraw(renderer);
	}

	bird.RenderDraw(renderer);
	ground.RenderDraw(renderer);

	RenderDrawUI();

	SDL_RenderPresent(renderer);
}

void Game::RenderDrawUI()
{
	switch (state)
	{
	case (GameState::StartScreen):
		getReadyBanner.RenderDraw(renderer);
		startBanner.RenderDraw(renderer);
		break;
	case (GameState::GameOver):
		gameOverBanner.RenderDraw(renderer);
		stats.Update(renderer, score.score());
		stats.RenderDraw(renderer);
		okButton.RenderDraw(renderer);
		break;
	}

	pauseButton.RenderDraw(renderer);
}

void Game::Update(float deltaTime, Uint64 nowTicks)
{
	if (pause)
		return;

	switch (state)
	{
	case (GameState::StartScreen):
		UpdateStartScreen(deltaTime, nowTicks);
		break;

	case (GameState::Playing):
		UpdatePlaying(deltaTime, nowTicks);
		break;

	default:
		UpdateGameOver(deltaTime, nowTicks);
		break;
	}
}

void Game::UpdateStartScreen(float deltaTime, Uint64 nowTicks)
{
	bird.IdleFly(deltaTime, nowTicks);
	background.Update(deltaTime);
	ground.Update(deltaTime);
}

void Game::UpdatePlaying(float deltaTime, Uint64 nowTicks)
{
	bird.Update(deltaTime, nowTicks);

	if (!bird.IsAlive())
	{
		state = GameState::GameOver;
		return;
	}

	background.Update(deltaTime);
	ground.Update(deltaTime);
	pipePairsManager.Update(deltaTime);
	UpdateCollision();
}

void Game::UpdateGameOver(float deltaTime, Uint64 nowTicks)
{
	bird.Update(deltaTime, nowTicks);
}

void Game::UpdateCollision()
{
	if (pipePairsManager.CheckCollisionWithPipePairs(bird.Rect()))
		bird.Death();
	else if (pipePairsManager.IsPassedBy(bird.Left()))
		score.Increment(renderer);
}

void Game::StartPlaying()
{
	state = GameState::Playing;
	bird.Flap();
}

void Game::Restart()
{
	state = GameState::StartScreen;
	Reset();
}

void Game::Reset()
{
	pipePairsManager.Reset();
	bird.Reset();
	score.Reset(renderer);
}

void Game::TogglePause() {
	pause = !pause;
	pauseButton.Switch();
}