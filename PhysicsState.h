#ifndef PHYSICSSTATE_H
#define PHYSICSSTATE_H

#include <set>
#include <memory>
#include "Vector2D.h"
#include "Collision.h"

class GameObject;

class PhysicsState {
public:
    explicit PhysicsState(GameObject *);

    ~PhysicsState();

    void change();

    void detectCollision(PhysicsState&);

    void free();

    Vector2D velocity;
    bool gravity = false;
    bool still = true;
    float gravityForce = 0.f;
    std::set<GameObject *> colliders;
protected:
    GameObject *gameObject = nullptr;
};

#endif // PHYSICSSTATE_H
