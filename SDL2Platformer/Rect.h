#pragma once
#include <SDL2/SDL.h>
#include "Vector2D.h"
#include "Size.h"
class Rect
{
public:
	Rect();
	Rect(float, float, float, float);
	Rect(Vector2D, Size);
	SDL_Rect SDLRect();
	Vector2D center;
	Size size;
};

