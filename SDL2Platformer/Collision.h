#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2D.h"

class GameObject;

class Collision
{
    public:
        Collision(GameObject *, Vector2D);
        GameObject * collider;
        Vector2D collisionVector;
};

#endif // COLLISION_H
