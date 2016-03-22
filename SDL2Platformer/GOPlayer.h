#pragma once
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"
#include "Animation.h"

class GameContext;

class GOPlayer :
	public GameObject
{
public:
	GOPlayer(GameContext *, Rect);
	void handleEvent(SDL_Event *);
	void handleKeyboard(const Uint8 *);
	void handleEnterCollision(Collision);
	void handleExitCollision(GameObject *);
	void handleCollision(Collision);
	void dealDamage(int);
	void die();
	void free();

	float speed = 0.0f;
	float jumpSpeed = 0.0f;
	bool jumped = false;
	Size originalSize;
	bool crouched = false;
	int health;

	Animation * idleAnimation = NULL;
	Animation * moveAnimation = NULL;
	Animation * jumpAnimation = NULL;
	Animation * crouchAnimation = NULL;
	Animation * crouchMoveAnimation = NULL;
protected:
	void setCrouched(bool);
};

