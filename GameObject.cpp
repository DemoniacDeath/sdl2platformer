#include "GameContext.h"
#include "GameObject.h"

GameObject::GameObject(const GameContext &ctx, const Rect frame) : context{ctx} {
    this->frame = frame;
}

void GameObject::handleEvent(SDL_Event *e) {
    for (auto &child: children) {
        child->handleEvent(e);
    }
}

void GameObject::handleKeyboard(const Uint8 *state) {
    for (auto &child: children) {
        child->handleKeyboard(state);
    }
}

void GameObject::processPhysics() {
    if (physics) {
        physics->change();
    }

    for (auto i = children.begin(); i != children.end(); ++i) {
        (*i)->processPhysics();
    }
}

void GameObject::detectCollisions() {
    std::vector<GameObject *> allColliders;
    detectCollisions(allColliders);
    for (Uint32 i = 0, size = allColliders.size(); i < size; ++i) {
        for (Uint32 j = i + 1; j < size; ++j) {
            allColliders[i]->physics->detectCollision(*(allColliders[j]->physics));
        }
    }
}

void GameObject::detectCollisions(std::vector<GameObject *> &allColliders) {
    if (physics) {
        allColliders.push_back(this);
    }
    for (const auto &child: children) {
        child->detectCollisions(allColliders);
    }
}

void GameObject::handleEnterCollision(__attribute__((unused)) Collision collision) {}

void GameObject::handleExitCollision(__attribute__((unused)) GameObject *collider) {}

void GameObject::handleCollision(__attribute__((unused)) Collision collision) {}

void GameObject::animate() {
    if (animation) {
        this->renderObject = animation->animate();
    }
    for (auto &child: children) {
        child->animate();
    }
}

void GameObject::render(Vector2D localBasis, Vector2D cameraPosition, Size cameraSize) {
    if (visible) {
        Vector2D globalPosition = frame.center;
        globalPosition += localBasis;
        renderObject.render(context.renderer, *(context.settings), globalPosition, frame.size, cameraPosition,
                            cameraSize);
    }
    for (const auto &child: children) {
        child->render(localBasis + frame.center, cameraPosition, cameraSize);
    }
}

void GameObject::addChild(GameObject *child) {
    child->parent = this;
    children.push_back(child);
}

Vector2D GameObject::globalPosition() {
    if (parent) {
        return frame.center + parent->globalPosition();
    } else {
        return frame.center;
    }
}
