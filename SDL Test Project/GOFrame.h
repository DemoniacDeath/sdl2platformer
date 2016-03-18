#pragma once
#include "GameObject.h"
#include "GOSolid.h"
class GOFrame :
	public GameObject
{
public:
	GOFrame(GameContext *, SDL_Rect, int);
	int width;
	GOSolid * floor, * wallLeft, * wallRight, * ceiling;
};

