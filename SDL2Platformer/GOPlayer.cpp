#include "GOPlayer.h"

GOPlayer::GOPlayer(GameContext * context, SDL_Rect rect) : GameObject(context, rect)
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
				physics->velocity += Vector2D(0, -jumpSpeed);
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
		moveVector += Vector2D(-speed, 0);
	}
	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
	{
		moveVector += Vector2D(speed, 0);
	}
	rect.x += moveVector.x;
	rect.y += moveVector.y;
	GameObject::handleKeyboard(state);
}

void GOPlayer::handleCollision(GameObject * collider, Vector2D collisionArea)
{
	if (SDL_abs(collisionArea.x) < SDL_abs(collisionArea.y))
	{
		rect.x -= collisionArea.x;
		physics->velocity.x = 0;
	}
	else
	{
		if (collisionArea.y > 0)
		{
			jumped = false;
		}
		rect.y -= collisionArea.y;
		physics->velocity.y = 0;
	}
}