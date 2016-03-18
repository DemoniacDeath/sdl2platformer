#include "PhysicsState.h"
#include "GameObject.h"

PhysicsState::PhysicsState(GameObject * object)
{
	gameObject = object;
	gravityForce = 0.5;
}

void PhysicsState::change()
{
	if (gravity)
	{
		velocity.y += gravityForce;
	}
	gameObject->rect.x += velocity.x;
	gameObject->rect.y += velocity.y;
}

void PhysicsState::detectCollision(PhysicsState * c)
{
	int x1 = gameObject->rect.x;
	int x2 = c->gameObject->rect.x;
	int X1 = x1 + gameObject->rect.w;
	int X2 = x2 + c->gameObject->rect.w;
	int y1 = gameObject->rect.y;
	int y2 = c->gameObject->rect.y;
	int Y1 = y1 + gameObject->rect.h;
	int Y2 = y2 + c->gameObject->rect.h;

	int diffX1 = X1 - x2;
	int diffX2 = x1 - X2;
	int diffY1 = Y1 - y2;
	int diffY2 = y1 - Y2;

	if (diffX1 > 0 &&
		diffX2 < 0 &&
		diffY1 > 0 &&
		diffY2 < 0)
	{
		Vector2D overlapArea = Vector2D(
			(SDL_abs(diffX1)<SDL_abs(diffX2) ? diffX1 : diffX2),
			(SDL_abs(diffY1)<SDL_abs(diffY2) ? diffY1 : diffY2)
			);
		gameObject->handleCollision(c->gameObject, overlapArea);
		c->gameObject->handleCollision(gameObject, overlapArea * -1);
	}
}