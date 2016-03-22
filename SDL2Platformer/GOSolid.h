#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"

class GOSolid :
	public GameObject
{
public:
	GOSolid(GameContext *, Rect);
	void handleCollision(Collision);
};

