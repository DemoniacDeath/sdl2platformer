#include "GOConsumable.h"

GOConsumable::GOConsumable(const GameContext &context, Rect frame) : GameObject(context, frame) {
    physics = std::make_shared<PhysicsState>(this);
}
