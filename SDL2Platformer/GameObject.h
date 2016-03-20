#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "Rect.h"
#include "RenderObject.h"
#include "PhysicsState.h"
#include "Animation.h"

class GameContext;

class GameObject
{
public:
	GameObject(GameContext *);
	GameObject(GameContext *, Rect);
	virtual void handleEvent(SDL_Event *);
	virtual void handleKeyboard(const Uint8 *);
	virtual void processPhysics();
	virtual void detectCollisions();
	virtual void detectCollisions(std::vector<GameObject *> *);
	virtual void handleCollision(GameObject *, Vector2D);
	virtual void handleExitCollision(GameObject *);
	virtual void animate();
	virtual void render(Vector2D, Vector2D, Size);
	virtual void addChild(GameObject *);
	virtual void free();
	Vector2D globalPosition();

	std::vector<GameObject *> children;
	RenderObject * renderObject = NULL;
	Animation * animation = NULL;
	PhysicsState * physics = NULL;
	Rect frame;
	GameObject * parent = NULL;
protected:
	GameContext * context = NULL;
};

