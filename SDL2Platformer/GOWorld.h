#pragma once
#include "GameObject.h"
class GOWorld :
	public GameObject
{
public:
	GOWorld(GameContext *, SDL_Rect);
	void handleEvent(SDL_Event *);
};

