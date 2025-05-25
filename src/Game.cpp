#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.hpp"
#include "Config.hpp"

Game::Game()
	: state(GameState::StartScreen),
	bird(renderer), ground(renderer), pipePairsManager(renderer),
	background(renderer, 0, 0, backgroundNightTextureFile, false),
	gameOverBanner(renderer, WINDOW_CENTER_X, 200, gameOverBannerTextureFile, true),
	getReadyBanner(renderer, WINDOW_CENTER_X, 200, getReadyBannerTextureFile, true),
	startBanner(renderer, WINDOW_CENTER_X, 520, startBannerTextureFile, true) {}

void Game::RenderDraw()
{
	background.RenderDraw(renderer);
	
	if (state != GameState::StartScreen)
		pipePairsManager.RenderDraw(renderer);

	ground.RenderDraw(renderer);
	bird.RenderDraw(renderer);

	RenderDrawUI();
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
		break;
	}
}

void Game::Update()
{
	switch (state)
	{
	case (GameState::StartScreen):
		UpdateStartScreen();
		break;
	case (GameState::Playing):
		UpdatePlaying();
		break;
	case (GameState::GameOver):
		UpdateGameOver();
		break;
	}
}

void Game::UpdateStartScreen()
{
	bird.IdleFly();
	ground.Update();
}

void Game::UpdatePlaying()
{
	bird.Update();

	if (!bird.IsAlive())
	{
		state = GameState::GameOver;
		return;
	}

	ground.Update();
	pipePairsManager.Update();
	UpdateCollision();
}

void Game::UpdateGameOver()
{
	bird.Update();
}

void Game::UpdateCollision()
{
	if (pipePairsManager.CheckCollisionWithPipePairs(bird.Rect()))
		bird.Death();
}

void Game::Iter()
{
	Update();
	RenderDraw();
	SDL_RenderPresent(renderer);
	SDL_Delay(DELAY_MS);
}

void Game::EventHandler(SDL_Event* event)
{
	switch (event->type)
	{
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
			if (state == GameState::Playing)
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
}