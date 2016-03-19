#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "GOCamera.h"
class GOWorld :
	public GameObject
{
public:
	GOWorld(GameContext *, Rect);
	void handleEvent(SDL_Event *);
	void render();
	GOCamera * camera;

};

