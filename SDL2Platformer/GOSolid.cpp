#include "GOSolid.h"

GOSolid::GOSolid(GameContext * context, Rect frame) : GameObject(context, frame)
{
	physics = new PhysicsState(this);
	physics->gravity = false;
}
