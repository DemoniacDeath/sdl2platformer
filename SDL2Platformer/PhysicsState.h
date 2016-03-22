#pragma once
#include <set>
#include "Vector2D.h"
#include "Collision.h"

class GameObject;

class PhysicsState
{
public:
	PhysicsState(GameObject *);
	~PhysicsState();
	void change();
	void detectCollision(PhysicsState *);
	void free();
	Vector2D velocity;
	bool gravity = false;
	bool still = true;
	float gravityForce = 0.f;
	std::set<GameObject *> colliders;
protected:
	GameObject * gameObject = NULL;
};

