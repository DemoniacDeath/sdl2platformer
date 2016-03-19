#include "GOPlayer.h"

GOPlayer::GOPlayer(GameContext * context, Rect frame) : GameObject(context, frame)
{
	physics = new PhysicsState(this);
	physics->gravity = true;
	jumped = false;
}

void GOPlayer::handleEvent(SDL_Event * e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_w:
		case SDLK_UP:
			if (!jumped)
			{
				physics->velocity += Vector2D(0, float(-jumpSpeed));
				jumped = true;
			}
			break;
		}
	}
	GameObject::handleEvent(e);
}

void GOPlayer::handleKeyboard(const Uint8 * state)
{
	Vector2D moveVector = Vector2D();
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
	{
		moveVector += Vector2D(float(-speed), 0);
	}
	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
	{
		moveVector += Vector2D(float(speed), 0);
	}
	frame.center.x += moveVector.x;
	frame.center.y += moveVector.y;
	GameObject::handleKeyboard(state);
}

void GOPlayer::handleCollision(GameObject * collider, Vector2D collisionArea)
{
	if (abs(collisionArea.x) < abs(collisionArea.y))
	{
		frame.center.x -= collisionArea.x;
		physics->velocity.x = 0;
	}
	else
	{
		if (collisionArea.y > 0 && jumped)
		{
			jumped = false;
		}
		frame.center.y -= collisionArea.y;
		physics->velocity.y = 0;
	}
}

void GOPlayer::handleExitCollision(GameObject * collider)
{
}