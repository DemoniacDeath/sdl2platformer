#pragma once
#include "Vector2D.h"

class GameObject;

class PhysicsState
{
public:
	PhysicsState(GameObject *);
	void change();
	void detectCollision(PhysicsState *);
	Vector2D velocity;
	bool gravity;
	float gravityForce;
protected:
	GameObject * gameObject;
};

