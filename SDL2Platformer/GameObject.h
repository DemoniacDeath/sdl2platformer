#pragma once
#include <SDL.h>
#include <vector>
#include "RenderObject.h"
#include "PhysicsState.h"

class GameContext;

class GameObject
{
public:
	GameObject(GameContext *);
	GameObject(GameContext *, SDL_Rect);
	virtual void handleEvent(SDL_Event *);
	virtual void handleKeyboard(const Uint8 *);
	virtual void processPhysics();
	virtual void detectCollisions();
	virtual void detectCollisions(std::vector<GameObject *> *);
	virtual void handleCollision(GameObject *, Vector2D);
	virtual void render();
	virtual void free();

	std::vector<GameObject *> children;
	RenderObject * renderObject;
	PhysicsState * physics;
	SDL_Rect rect;
protected:
	GameContext * context;
};

