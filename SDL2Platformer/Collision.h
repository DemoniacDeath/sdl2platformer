#pragma once
#include "Vector2D.h"

class GameObject;

class Collision
{
public:
	Collision(GameObject *, Vector2D);
	GameObject * collider;
	Vector2D collisionVector;
};

