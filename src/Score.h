#pragma once

#include <SDL3/SDL.h>

#include <array>

#include "GameObjectBase.h"
#include "NumberDisplay.h"

class Score : public GameObjectBase, public NumberDisplay
{
public:
	Score(SDL_Renderer* renderer);
	~Score();

	inline size_t score() const { return _score; }

	void RenderDraw(SDL_Renderer* renderer) const override;
	void Increment(SDL_Renderer* renderer);
	void Reset(SDL_Renderer* renderer);

private:
	SDL_Texture* texture;
	size_t _score;

	void UpdateTexture(SDL_Renderer* renderer);
};

