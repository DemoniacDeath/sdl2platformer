#include "GOSolid.h"

GOSolid::GOSolid(GameContext * context, Rect frame) : GameObject(context, frame)
{
	physics = new PhysicsState(this);
}

void GOSolid::handleCollision(Collision collision)
{
	GameObject * collider;
	Vector2D collisionArea;
	collisionArea = collision.collisionVector;
	if (collision.firstCollider == this)
	{
		collisionArea *= -1;
		collider = collision.secondCollider;
	}
	else
	{
		collider = collision.firstCollider;
	}
	if (abs(collisionArea.x) < abs(collisionArea.y))
	{
		collider->frame.center.x -= collisionArea.x;
		collider->physics->velocity.x = 0;
	}
	else
	{
		collider->frame.center.y -= collisionArea.y;
		collider->physics->velocity.y = 0;
	}
}

