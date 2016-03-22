#pragma once
#include "GameObject.h"

class GameContext;

class GOConsumable :
	public GameObject
{
public:
	GOConsumable(GameContext *, Rect);
};

