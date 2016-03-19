#pragma once
#include "GameObject.h"
#include "GOSolid.h"
#include "Rect.h"
class GOFrame :
	public GameObject
{
public:
	GOFrame(GameContext *, Rect, int);
	int width;
	GOSolid * floor, * wallLeft, * wallRight, * ceiling;
};

