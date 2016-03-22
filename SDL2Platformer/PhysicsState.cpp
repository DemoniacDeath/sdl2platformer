#include "PhysicsState.h"
#include "GameObject.h"

PhysicsState::PhysicsState(GameObject * object)
{
	gameObject = object;
}

PhysicsState::~PhysicsState()
{
	free();
}

void PhysicsState::change()
{
	if (gravity)
	{
		velocity.y += gravityForce;
	}
	gameObject->frame.center.x += velocity.x;
	gameObject->frame.center.y += velocity.y;
}

void PhysicsState::detectCollision(PhysicsState * c)
{
	if (still && c->still)
		return;

	float x1 = gameObject->globalPosition().x - gameObject->frame.size.width / 2;
	float x2 = c->gameObject->globalPosition().x - c->gameObject->frame.size.width / 2;
	float X1 = x1 + gameObject->frame.size.width;
	float X2 = x2 + c->gameObject->frame.size.width;
	float y1 = gameObject->globalPosition().y - gameObject->frame.size.height / 2;
	float y2 = c->gameObject->globalPosition().y - c->gameObject->frame.size.height / 2;
	float Y1 = y1 + gameObject->frame.size.height;
	float Y2 = y2 + c->gameObject->frame.size.height;

	float diffX1 = X1 - x2;
	float diffX2 = x1 - X2;
	float diffY1 = Y1 - y2;
	float diffY2 = y1 - Y2;

	bool alreadyCollided = (
		colliders.find(c->gameObject) != colliders.end()
		||
		c->colliders.find(gameObject) != c->colliders.end()
		);
	if (diffX1 > 0 &&
		diffX2 < 0 &&
		diffY1 > 0 &&
		diffY2 < 0)
	{
		Vector2D overlapArea = Vector2D(
			(abs(diffX1)<abs(diffX2) ? diffX1 : diffX2),
			(abs(diffY1)<abs(diffY2) ? diffY1 : diffY2)
			);
		if (!alreadyCollided)
		{
			colliders.insert(c->gameObject);
			c->colliders.insert(gameObject);

			gameObject->handleEnterCollision(Collision(c->gameObject, overlapArea));
			c->gameObject->handleEnterCollision(Collision(gameObject, overlapArea * -1));
		}
		gameObject->handleCollision(Collision(c->gameObject, overlapArea));
		c->gameObject->handleCollision(Collision(gameObject, overlapArea * -1));
	}
	else if (alreadyCollided)
	{
		colliders.erase(c->gameObject);
		c->colliders.erase(gameObject);
		gameObject->handleExitCollision(c->gameObject);
		c->gameObject->handleExitCollision(gameObject);
	}
}

void PhysicsState::free()
{
	for (std::set<GameObject *>::const_iterator i = colliders.begin(); i != colliders.end(); ++i)
	{
		(*i)->physics->colliders.erase(gameObject);
	}
	colliders.clear();
}