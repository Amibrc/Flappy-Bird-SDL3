#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.h"
#include "Config.h"

#include <iostream>

Game::Game()
	: state(GameState::StartScreen),
	lastTicks(SDL_GetTicks()), bird(renderer), pipePairsManager(renderer),
	background(renderer, 0, backgroundNightFile, BACKGROUND_MOVE_SPEED),
	ground(renderer, GROUND_Y, groundFile, GROUND_MOVE_SPEED),
	gameOverBanner(renderer, WINDOW_CENTER_X, 200, gameOverBannerFile, true),
	getReadyBanner(renderer, WINDOW_CENTER_X, 200, getReadyBannerFile, true),
	startBanner(renderer, WINDOW_CENTER_X, 520, startBannerFile, true),
	score(renderer), stats(renderer) {}

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
		if (state == GameState::Playing)
			bird.Flap();
		else if (state == GameState::GameOver)
			Restart();
		else
			StartPlaying();
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.scancode)
		{
		case (SDL_SCANCODE_SPACE):
			if (event->key.repeat)
				break;
			else if (state == GameState::Playing)
				bird.Flap();
			else if (state == GameState::GameOver)
				Restart();
			else
				StartPlaying();
			break;
		case (SDL_SCANCODE_ESCAPE):
			if (state != GameState::StartScreen)
			{
				Reset();
				state = GameState::StartScreen;
			}
			break;
		}
		break;
	}

	return SDL_APP_CONTINUE;
}

void Game::RenderDraw()
{
	background.RenderDraw(renderer);
	
	if (state != GameState::StartScreen)
	{
		pipePairsManager.RenderDraw(renderer);
		score.RenderDraw(renderer);
	}

	ground.RenderDraw(renderer);
	bird.RenderDraw(renderer);

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
		break;
	}
}

void Game::Update(float deltaTime, Uint64 nowTicks)
{
	switch (state)
	{
	case (GameState::StartScreen):
		UpdateStartScreen(deltaTime, nowTicks);
		break;
	case (GameState::Playing):
		UpdatePlaying(deltaTime, nowTicks);
		break;
	case (GameState::GameOver):
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
	Reset();
	StartPlaying();
}

void Game::Reset()
{
	pipePairsManager.Reset();
	bird.Reset();
	score.Reset(renderer);
}