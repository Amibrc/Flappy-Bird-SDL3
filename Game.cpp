#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Game.hpp"
#include "Collider.hpp"
#include "Config.hpp"

Game::Game()
{
	SDL_srand(SDL_GetPerformanceCounter());

	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Log("Error: SDL_Init - %s\n", SDL_GetError());

	if (!SDL_CreateWindowAndRenderer("Flappy Bird", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
		SDL_Log("Error: SDL_CreateWindowAndRenderer - %s\n", SDL_GetError());

	if (!SDL_SetWindowIcon(window, IMG_Load(iconTextureFile)))
		SDL_Log("Error: SDL_SetWindowIcon - %s\n", SDL_GetError());

	bird = new Bird(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	background = new GameObject(renderer, 0, 0, backgroundNightTextureFile);
	grass = new GameObject(renderer, 0, GROUND_Y, grassTextureFile);
	pipePairsManager = new PipePairsManager(renderer, 350);
}

Game::~Game()
{
	delete bird;
	delete background;
	delete pipePairsManager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::RenderDraw()
{
	background->RenderDraw(renderer);
	pipePairsManager->RenderDraw(renderer);
	grass->RenderDraw(renderer);
	bird->RenderDraw(renderer);
}

void Game::Update()
{
	bird->Update();

	if (bird->IsAlive())
	{
		pipePairsManager->Update();
		UpdateCollision();
	}
}

void Game::UpdateCollision()
{
	if (pipePairsManager->CheckCollisionWithPipePairs(&bird->rect))
		bird->Death();
}

void Game::Iter()
{
	Update();
	RenderDraw();
}

void Game::EventHandler(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		if (bird->IsAlive())
			bird->Flap();
		else
			Restart();
		break;
	case SDL_EVENT_KEY_DOWN:
		if (event->key.scancode == SDL_SCANCODE_SPACE)
			if (bird->IsAlive())
				bird->Flap();
			else
				Restart();
		break;
	}
}

void Game::Restart()
{
	pipePairsManager->Reset();
	bird->Reset();
}
