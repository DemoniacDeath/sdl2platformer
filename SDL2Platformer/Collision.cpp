#include "Collision.h"
#include "GameObject.h"


Collision::Collision(GameObject *collider, Vector2D vector) {
    this->collider = collider;
    collisionVector = vector;
}
