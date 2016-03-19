#pragma once
#include "GameObject.h"
#include "Rect.h"
class GOPlayer :
	public GameObject
{
public:
	GOPlayer(GameContext *, Rect);
	void handleEvent(SDL_Event *);
	void handleKeyboard(const Uint8 *);
	void handleCollision(GameObject *, Vector2D);

	int speed;
	int jumpSpeed;
	bool jumped;
};

