#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.hpp"
#include "Config.hpp"

Game::Game()
	: state(GameState::startScreen),
	bird(renderer), ground(renderer), pipePairsManager(renderer),
	background(renderer, 0, 0, backgroundNightTextureFile, false),
	gameOverBanner(renderer, WINDOW_CENTER_X, 200, gameOverBannerTextureFile, true),
	getReadyBanner(renderer, WINDOW_CENTER_X, 200, getReadyBannerTextureFile, true) {}

void Game::RenderDraw()
{
	background.RenderDraw(renderer);
	
	if (state != GameState::startScreen)
		pipePairsManager.RenderDraw(renderer);

	ground.RenderDraw(renderer);
	bird.RenderDraw(renderer);

	RenderDrawUI();
}

void Game::RenderDrawUI()
{
	switch (state)
	{
	case (GameState::startScreen):
		getReadyBanner.RenderDraw(renderer);
		break;
	case (GameState::gameOver):
		gameOverBanner.RenderDraw(renderer);
		break;
	}
}

void Game::Update()
{
	switch (state)
	{
	case (GameState::startScreen):
		UpdateStartScreen();
		break;
	case (GameState::playing):
		UpdatePlaying();
		break;
	case (GameState::gameOver):
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
		state = GameState::gameOver;
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
		if (state == GameState::playing)
			bird.Flap();
		else if (state == GameState::gameOver)
			Restart();
		else
			StartPlaying();
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.scancode)
		{
		case (SDL_SCANCODE_SPACE):
			if (state == GameState::playing)
				bird.Flap();
			else if (state == GameState::gameOver)
				Restart();
			else
				StartPlaying();
			break;
		case (SDL_SCANCODE_ESCAPE):
			state = GameState::startScreen;
			break;
		}
		break;
	}
}

void Game::StartPlaying()
{
	state = GameState::playing;
	bird.Flap();
}

void Game::Restart()
{
	pipePairsManager.Reset();
	bird.Reset();
	StartPlaying();
}
