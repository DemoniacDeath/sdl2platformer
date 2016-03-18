#pragma once
#include <SDL.h>
#include "Color.h"

class GameContext;

class RenderObject
{
public:
	RenderObject(GameContext * context, SDL_Texture * texture);
	RenderObject(GameContext * context, SDL_Rect rect, Color color);
	void free();
	SDL_Texture * texture;
private:
	GameContext * context;
};
