#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "TextureManager.h"

#include "Game.h"
#include "Config.h"
#include "Collider.h"

Game::Game()
	// ==== States ====
	: pause(false),
	state(GameState::MainScreen),
	lastTicks(SDL_GetTicks()),

	// ==== Game objects ====
	bird(renderer, 450, 100, false),
	pipePairsManager(renderer),
	background(renderer, 0, BACKGROUND_DAY_FILE, BACKGROUND_MOVE_SPEED),
	ground(renderer, BOTTOM_GROUND_Y, GROUND_FILE, GROUND_MOVE_SPEED),

	// ==== UI ====
	gameOverBanner(renderer, WINDOW_CENTER_X, 200, GAME_OVER_BANNER_FILE, true),
	getReadyBanner(renderer, WINDOW_CENTER_X, 200, GET_READY_BANNER_FILE, true),
	startBanner(renderer, WINDOW_CENTER_X, 520, START_BANNER_FILE, true),
	flappyBirdBanner(renderer, WINDOW_CENTER_X - 20, 200, FLAPPY_BIRD_BANNER_FILE, true),
	startButton(renderer, WINDOW_CENTER_X, 550, START_BUTTON_FILE, true),
	menuButton(renderer, WINDOW_CENTER_X + 115, 600, MENU_BUTTON_FILE, true),
	okButton(renderer, WINDOW_CENTER_X - 115, 600, OK_BUTTON_FILE, true),
	pauseButton(renderer, 20, 20, PAUSE_BUTTON_FILES, 2, false),

	// ==== Score / Stats ====
	score(renderer),
	stats(renderer) {}

Game::~Game()
{
	TextureManager::Clear();
}

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
	if (state != GameState::MainScreen && pauseButton.IsClicked(x, y))
	{
		TogglePause();
		return;
	}
	else if (state == GameState::GameOver && okButton.IsClicked(x, y))
	{
		Restart();
		bird.SetCenterY(WINDOW_CENTER_Y);
		return;
	}
	else if (state == GameState::MainScreen && startButton.IsClicked(x, y))
	{
		state = GameState::StartScreen;
		bird.SetIdleBaseY(WINDOW_CENTER_Y);
		bird.SetCenterX(WINDOW_CENTER_X);
		bird.SetCenterY(WINDOW_CENTER_Y);
		return;
	}
	else if (state == GameState::GameOver && menuButton.IsClicked(x, y))
	{
		state = GameState::MainScreen;
		PauseOff();
		Reset();
		bird.SetIdleBaseY(100);
		bird.SetX(450);
		bird.SetY(100);
		return;
	}

	if (pause)
		return;
	
	HandleGameAction();
}

void Game::HandleKeyPress(const SDL_KeyboardEvent* keyEvent)
{
	if (keyEvent->repeat)
		return;

	switch (keyEvent->scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		TogglePause();
		break;

	case SDL_SCANCODE_SPACE:
	case SDL_SCANCODE_UP:
		if (!pause)
			HandleGameAction();
		break;

	case SDL_SCANCODE_RETURN:
		if (state == GameState::GameOver)
		{
			Restart();
			bird.SetCenterY(WINDOW_CENTER_Y);
		}
		else if (state == GameState::MainScreen)
		{
			state = GameState::StartScreen;
			bird.SetIdleBaseY(WINDOW_CENTER_Y);
			bird.SetCenterY(WINDOW_CENTER_Y);
			bird.SetCenterX(WINDOW_CENTER_X);
		}
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
	
	if (state == GameState::Playing || state == GameState::GameOver)
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
	case (GameState::MainScreen):
		flappyBirdBanner.RenderDraw(renderer);
		startButton.RenderDraw(renderer);
		break;

	case (GameState::StartScreen):
		getReadyBanner.RenderDraw(renderer);
		startBanner.RenderDraw(renderer);
		pauseButton.RenderDraw(renderer);
		break;

	case (GameState::Playing):
		pauseButton.RenderDraw(renderer);
		break;

	case (GameState::GameOver):
		gameOverBanner.RenderDraw(renderer);
		stats.Update(renderer, score.score());
		stats.RenderDraw(renderer);
		menuButton.RenderDraw(renderer);
		okButton.RenderDraw(renderer);
		pauseButton.RenderDraw(renderer);
		break;
	}
}

void Game::Update(float deltaTime, Uint64 nowTicks)
{
	if (pause)
		return;

	switch (state)
	{
	case (GameState::MainScreen):
		UpdateMainScreen(deltaTime, nowTicks);
		break;

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

void Game::UpdateMainScreen(float deltaTime, Uint64 nowTicks)
{
	bird.IdleFly(deltaTime, nowTicks);
	flappyBirdBanner.SetCenterY(bird.CenterY());
	background.Update(deltaTime);
	ground.Update(deltaTime);
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

void Game::TogglePause()
{
	pause = !pause;
	pauseButton.Switch();
}

void Game::PauseOff()
{
	if (pause)
	{
		pause = false;
		pauseButton.Switch();
	}
}