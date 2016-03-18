#include "GOSolid.h"

GOSolid::GOSolid(GameContext * context, SDL_Rect rect) : GameObject(context, rect)
{
	physics = new PhysicsState(this);
	physics->gravity = false;
}
