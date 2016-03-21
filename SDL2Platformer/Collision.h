#pragma once
#include "Vector2D.h"

class GameObject;

class Collision
{
public:
	Collision(GameObject *, GameObject *, Vector2D);
	GameObject * firstCollider;
	GameObject * secondCollider;
	Vector2D collisionVector;
};

