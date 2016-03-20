#pragma once
#include <SDL.h>
#include "Color.h"

class GameContext;
class GameObject;

class RenderObject
{
public:
	RenderObject(GameContext *, SDL_Texture *);
	RenderObject(GameContext *, GameObject *, Color);
	void free();
	SDL_Texture * texture;
};
