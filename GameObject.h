#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <memory>
#include "Rect.h"
#include "RenderObject.h"
#include "PhysicsState.h"
#include "Animation.h"
#include "Collision.h"

class GameContext;

class GameObject {
public:
    GameObject(const GameContext &, Rect);

    virtual ~GameObject() = default;

    virtual void handleEvent(SDL_Event *);

    virtual void handleKeyboard(const Uint8 *);

    virtual void processPhysics();

    virtual void detectCollisions();

    virtual void detectCollisions(std::vector<GameObject *> &);

    virtual void handleEnterCollision(Collision __unused);

    virtual void handleExitCollision(GameObject *);

    virtual void handleCollision(Collision);

    virtual void animate();

    virtual void render(Vector2D, Vector2D, Size);

    virtual void addChild(GameObject *);

    Vector2D globalPosition();

    std::vector<GameObject *> children;
    RenderObject renderObject;
    Animation *animation = nullptr;
    std::shared_ptr<PhysicsState> physics;
    Rect frame;
    bool visible = true;
    bool removed = false;

protected:
    GameObject *parent = nullptr;
    const GameContext &context;
};

#endif // GAMEOBJECT_H
