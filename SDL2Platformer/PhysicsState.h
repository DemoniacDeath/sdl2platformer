#pragma once
#include <set>
#include "Vector2D.h"
#include "Collision.h"

class GameObject;

class PhysicsState
{
public:
	PhysicsState(GameObject *);
	void change();
	void detectCollision(PhysicsState *);
	Vector2D velocity;
	bool gravity = false;
	bool still = true;
	float gravityForce = 0.f;
	std::set<Collision *> collisions;
protected:
	GameObject * gameObject = NULL;
};

