#include "Collision.h"
#include "GameObject.h"


Collision::Collision(GameObject * first, GameObject * second, Vector2D vector)
{
	firstCollider = first;
	secondCollider = second;
	collisionVector = vector;
}
