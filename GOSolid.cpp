#include "GOSolid.h"
#include "GOPlayer.h"

GOSolid::GOSolid(const GameContext& context, Rect frame) : GameObject(context, frame) {
    physics = std::make_shared<PhysicsState>(this);
}

void GOSolid::handleEnterCollision(Collision collision) {
    GOPlayer *player;
    if (collision.collider->physics->velocity.y > 5 && (player = dynamic_cast<GOPlayer *>(collision.collider))) {
        player->dealDamage((int) roundf(collision.collider->physics->velocity.y * 10));
    }
}

void GOSolid::handleCollision(Collision collision) {
    if (fabs(collision.collisionVector.x) < fabs(collision.collisionVector.y)) {
        collision.collider->frame.center.x += collision.collisionVector.x;
        collision.collider->physics->velocity.x = 0;
    } else {
        collision.collider->frame.center.y += collision.collisionVector.y;
        collision.collider->physics->velocity.y = 0;
    }
}

