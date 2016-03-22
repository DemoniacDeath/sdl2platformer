#include "GOConsumable.h"

GOConsumable::GOConsumable(GameContext * context, Rect frame) : GameObject(context, frame)
{
	physics = new PhysicsState(this);
}
