#pragma once

#include <SDL3/SDL.h>

#include "Game.h"

class IGameState
{
public:
	~IGameState() = default;
	virtual void RenderDraw(SDL_Renderer* renderer) const = 0;
	virtual void Update(float deltaTime, Uint64 nowTicks) = 0;
	virtual void HandleMouseClick(float x, float y) = 0;
	virtual void HandleKeyPress(const SDL_KeyboardEvent* keyEvent) = 0;
};

class MainScreenState : public IGameState
{
public:
	MainScreenState(Game* game);
	~MainScreenState() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update(float deltaTime, Uint64 nowTicks) override;
	virtual void HandleMouseClick(float x, float y) override;
	virtual void HandleKeyPress(const SDL_KeyboardEvent* keyEvent) override;

private:
	Game* game;
};

class StartScreenState : public IGameState
{
public:
	StartScreenState(Game* game);
	~StartScreenState() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update(float deltaTime, Uint64 nowTicks) override;
	virtual void HandleMouseClick(float x, float y) override;
	virtual void HandleKeyPress(const SDL_KeyboardEvent* keyEvent) override;

private:
	Game* game;
};

class PlayingState : public IGameState
{
public:
	PlayingState(Game* game);
	~PlayingState() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update(float deltaTime, Uint64 nowTicks) override;
	virtual void HandleMouseClick(float x, float y) override;
	virtual void HandleKeyPress(const SDL_KeyboardEvent* keyEvent) override;

private:
	Game* game;
};

class GameOverState : public IGameState
{
public:
	GameOverState(Game* game);
	~GameOverState() = default;

	virtual void RenderDraw(SDL_Renderer* renderer) const override;
	virtual void Update(float deltaTime, Uint64 nowTicks) override;
	virtual void HandleMouseClick(float x, float y) override;
	virtual void HandleKeyPress(const SDL_KeyboardEvent* keyEvent) override;

private:
	Game* game;
};
