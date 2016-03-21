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
	void free();

	float speed = 0.0f;
	float jumpSpeed = 0.0f;
	bool jumped = false;
	Size originalSize;
	bool crouched = false;

	Animation * idleAnimation = NULL;
	Animation * moveAnimation = NULL;
	Animation * jumpAnimation = NULL;
	Animation * crouchAnimation = NULL;
	Animation * crouchMoveAnimation = NULL;
protected:
	void setCrouched(bool);
};

